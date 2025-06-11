// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_WaitAll.h"


#include "BeamK2.h"
#include "BeamFlow/ApiRequest/K2BeamNode_ApiRequest.h"

#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "K2Node_CreateDelegate.h"
#include "K2Node_MakeArray.h"
#include "ToolMenu.h"
#include "Framework/Notifications/NotificationManager.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "RequestTracker/BeamWaitHandle.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Misc/DefaultValueHelper.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "ScopedTransaction.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_WaitAll"


using namespace BeamK2;

const FName UK2BeamNode_WaitAll::SelfFunctionName = GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, GetSelf);
const FName UK2BeamNode_WaitAll::WaitAllFunctionName = GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, WaitAll);

const FName UK2BeamNode_WaitAll::P_CompleteCallback = FName("OnComplete");
const FName UK2BeamNode_WaitAll::P_RequestContexts = FName("RequestContexts");
const FName UK2BeamNode_WaitAll::P_Operations = FName("Operations");
const FName UK2BeamNode_WaitAll::P_Waits = FName("Waits");
const FName UK2BeamNode_WaitAll::P_Evt = FName("Evt");

FText UK2BeamNode_WaitAll::GetMenuCategory() const
{
	return LOCTEXT("BeamNodeCategory", "Beam|Operations");
}

FText UK2BeamNode_WaitAll::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("BeamNodeTitle", "Beam - Operations - Utils - Wait All");
}

void UK2BeamNode_WaitAll::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	// Create the input execution flow pin
	const auto _ = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

	// Create the output pins in an order that improves usability.
	const auto SynchronousFlowPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	const auto WaitHandle = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FBeamWaitHandle::StaticStruct(), TEXT("WaitHandle"));
	SynchronousFlowPin->PinFriendlyName = LOCTEXT("BeamNode", "Synchronous Flow");
	WaitHandle->PinToolTip = TEXT("");

	for (int i = 0; i < NumPins; ++i)
		CreateContextInputPin(i);

	if (bIsInBeamFlowMode)
		CreateBeamFlowModePins();
	else
		ParseFunctionForNodeInputPins(this, FindFunctionByName<UBeamRequestTracker>(WaitAllFunctionName), {P_CompleteCallback}, true);
}

UEdGraphPin* UK2BeamNode_WaitAll::CreateContextInputPin(const int32 PinIdx)
{
	// To see a bit more about how Wildcard pins work, take a look at (Search the project for this type): UK2Node_GetArrayItem
	const auto PinName = FName(FString::Printf(TEXT("Dependency - %d"), PinIdx));
	return CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, PinName);
}

void UK2BeamNode_WaitAll::AddInputPin()
{
	FScopedTransaction Transaction(LOCTEXT("AddPinTx", "AddPin"));
	Modify();

	const auto AddedPin = CreateContextInputPin(NumPins);
	NumPins += 1;

	// We do this so that the on complete callback always stays at the bottom.
	if (const auto DelegatePin = FindPin(P_CompleteCallback))
		Pins.Swap(Pins.IndexOfByKey(AddedPin), Pins.IndexOfByKey(DelegatePin));

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}

void UK2BeamNode_WaitAll::RemoveInputPin(UEdGraphPin* Pin)
{
	FScopedTransaction Transaction(LOCTEXT("RemovePinTx", "RemovePin"));
	Modify();

	int32 PinRemovalIndex = INDEX_NONE;
	if (Pins.Find(Pin, /*out*/ PinRemovalIndex))
	{
		const FString RemovedPinLastCharacter = FString::Printf(TEXT("%c"), Pin->GetDisplayName().ToString()[Pin->PinName.GetStringLength() - 1]);
		int32 RemovedPinNameIdx;
		FDefaultValueHelper::ParseInt(RemovedPinLastCharacter, RemovedPinNameIdx);

		Pins.RemoveAt(PinRemovalIndex);
		Pin->MarkAsGarbage();
		NumPins -= 1;

		for (int32 PinIndex = 0; PinIndex < Pins.Num(); ++PinIndex)
		{
			UEdGraphPin* LocalPin = Pins[PinIndex];
			check(LocalPin)
			if (LocalPin && LocalPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct && LocalPin->Direction == EGPD_Input)
			{
				const FString PinNameLastCharacter = FString::Printf(TEXT("%c"), LocalPin->GetDisplayName().ToString()[LocalPin->PinName.GetStringLength() - 1]);
				int PinNameIdx;
				FDefaultValueHelper::ParseInt(PinNameLastCharacter, PinNameIdx);
				if (PinNameIdx > RemovedPinNameIdx)
				{
					LocalPin->Modify();
					LocalPin->PinName = FName(FString::Printf(TEXT("Dependency - %d"), PinNameIdx - 1));
				}
			}
		}
		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	}
}

bool UK2BeamNode_WaitAll::CanRemovePin(const UEdGraphPin* Pin) const
{
	return (
		Pin &&
		NumPins &&
		(INDEX_NONE != Pins.IndexOfByKey(Pin)) &&
		(EEdGraphPinDirection::EGPD_Input == Pin->Direction)
	);
}

void UK2BeamNode_WaitAll::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);

	// If it's a wildcard pin that was changed.
	if (Pin->PinName.ToString().StartsWith(TEXT("Dependency")))
		PropagatePinType(Pin);
}

void UK2BeamNode_WaitAll::PostReconstructNode()
{
	Super::PostReconstructNode();

	for (const auto& Pin : Pins)
	{
		if (!Pin->PinName.ToString().StartsWith(TEXT("Dependency"))) continue;
		PropagatePinType(Pin);
	}
}

void UK2BeamNode_WaitAll::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);


	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Create nodes calling the GetSelf method of the UBeamBackend and the WaitAll function
	const auto CallSelfNode = CreateCallFunctionNode(this, CompilerContext, SourceGraph, SelfFunctionName, UBeamRequestTracker::StaticClass());
	const auto CallWaitAllNode = CreateCallFunctionNode(this, CompilerContext, SourceGraph, WaitAllFunctionName, UBeamRequestTracker::StaticClass());

	// Link the CallSelf node to the CallWaitAll node
	const auto bConnectedSubsystemToFunctionCall = K2Schema->TryCreateConnection(CallSelfNode->GetReturnValuePin(), K2Schema->FindSelfPin(*CallWaitAllNode, EGPD_Input));
	check(bConnectedSubsystemToFunctionCall)


	// Gets a list of all input pins that are structs in this wrapper node.
	TArray<UEdGraphPin*> RequestContextPins;
	TArray<UEdGraphPin*> OperationHandlePins;
	TArray<UEdGraphPin*> WaitHandlePins;
	for (const auto& Pin : Pins)
	{
		if (!Pin->PinName.ToString().StartsWith(TEXT("Dependency"))) continue;

		if (Pin->PinType.PinSubCategoryObject == FBeamRequestContext::StaticStruct())
			RequestContextPins.Add(Pin);

		if (Pin->PinType.PinSubCategoryObject == FBeamOperationHandle::StaticStruct())
			OperationHandlePins.Add(Pin);

		if (Pin->PinType.PinSubCategoryObject == FBeamWaitHandle::StaticStruct())
			WaitHandlePins.Add(Pin);
	}

	const auto ExpandMakeArrayNodes = [this](FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, const UK2Node_CallFunction* CallWaitAllNode, const FName WaitAllInputParam,
	                                         TArray<UEdGraphPin*> ArrayContentPins) -> UEdGraphPin*
	{
		const UEdGraphSchema_K2* K2 = GetDefault<UEdGraphSchema_K2>();

		// Creates a make array node with the same amount of Struct pins as we have here.
		const auto MakeArrayNode = CreateMakeArrayNode(this, CompilerContext, SourceGraph, ArrayContentPins.Num());

		// Connect the output pin of the make array node to the input Contexts the WaitAll node requires
		const auto MakeArrayOutputPin = MakeArrayNode->GetOutputPin();
		const auto CallWaitAllContextPin = CallWaitAllNode->FindPin(WaitAllInputParam);
		const auto bDidConnectMakeArrayResultPin = K2->TryCreateConnection(MakeArrayOutputPin, CallWaitAllContextPin);
		check(bDidConnectMakeArrayResultPin)

		// Move all pins connected to the Context input pins in the wrapper node to the MakeArray intermediate node
		auto MakeArrayNodeInputPins = MakeArrayNode->Pins.FilterByPredicate([](const UEdGraphPin* P) { return P->Direction == EGPD_Input; });
		check(MakeArrayNode->NumInputs == ArrayContentPins.Num())
		for (int i = 0; i < MakeArrayNodeInputPins.Num(); ++i)
		{
			const auto bDidMoveInputPin = CompilerContext.MovePinLinksToIntermediate(*ArrayContentPins[i], *MakeArrayNodeInputPins[i]);
			check(!bDidMoveInputPin.IsFatal())
		}

		return MakeArrayOutputPin;
	};

	if (RequestContextPins.Num() > 0)
		ExpandMakeArrayNodes(CompilerContext, SourceGraph, CallWaitAllNode, P_RequestContexts, RequestContextPins);

	if (OperationHandlePins.Num() > 0)
		ExpandMakeArrayNodes(CompilerContext, SourceGraph, CallWaitAllNode, P_Operations, OperationHandlePins);

	if (WaitHandlePins.Num() > 0)
		ExpandMakeArrayNodes(CompilerContext, SourceGraph, CallWaitAllNode, P_Waits, WaitHandlePins);


	// Get the execution pin from the CallWaitAll node
	const auto CallWaitAllExecPin = K2Schema->FindExecutionPin(*CallWaitAllNode, EGPD_Input);
	const auto MovedRegularExecutionFlow = CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CallWaitAllExecPin);
	check(!MovedRegularExecutionFlow.IsFatal())

	// Handle event mode shifts vs non-eventmode shifts
	if (bIsInBeamFlowMode)
	{
		const UK2Node_Event* CompleteEventNode = CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, TEXT("OnWaitComplete"));

		// Get all the pins we have on this custom node
		const auto OnCompleteFlowPin = FindPin(P_CompleteCallback);
		const auto EventPin = FindPinChecked(P_Evt);		

		const TArray<UEdGraphPin*> StartingGraphs{OnCompleteFlowPin,};
		const TArray<FName> RelevantEventSpawningFunctionNames{GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, WaitAll)};
		TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
		TArray<TArray<UEdGraphNode*>> OutPerEventFlowNodes;
		GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, RelevantEventSpawningFunctionNames, OutPerFlowNodes, OutPerEventFlowNodes);

		const auto WaitAllOnCompletePin = CallWaitAllNode->FindPinChecked(P_CompleteCallback, EGPD_Input);

		const auto CompleteEventNodeExecPin = CompleteEventNode->FindPin(UEdGraphSchema_K2::PN_Then);
		const auto CompleteEventDelegatePin = CompleteEventNode->FindPinChecked(CompleteEventNode->DelegateOutputName);
		const auto CompleteEventContextsPin = CompleteEventNode->FindPinChecked(P_Evt);		


		// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
		const TArray<UEdGraphPin*> CompletePins{EventPin,};
		const TArray<UEdGraphPin*> CompleteEventPins{CompleteEventContextsPin,};
		ReplaceConnectionsOnBeamFlow(OutPerFlowNodes[0], CompletePins, CompleteEventPins);
		ReplaceConnectionsOnBeamFlow(OutPerEventFlowNodes[0], CompletePins, CompleteEventPins);

		// Move the execution flow from the "On Complete" pin to the "Then" execution pin of the CompleteEvent node.  
		const auto ExecFlowMoved = CompilerContext.MovePinLinksToIntermediate(*OnCompleteFlowPin, *CompleteEventNodeExecPin);
		check(!ExecFlowMoved.IsFatal());

		// Connect the CompleteEventNode's "OutputDelegate" pin to the "____ Request" Wait All Call Function node "OnComplete" delegate pin.
		const auto bConnectedDelegatePins = K2Schema->TryCreateConnection(CompleteEventDelegatePin, WaitAllOnCompletePin);
		check(bConnectedDelegatePins)
	}
	else
	{
		// Move the synchronous execution flow over to the call wait node 
		MoveWrappedPin(this, CompilerContext, CallWaitAllNode, UEdGraphSchema_K2::PN_Then);

		// Move the on complete delegate pin over to the call wait node.
		MoveWrappedPin(this, CompilerContext, CallWaitAllNode, P_CompleteCallback);
	}

	BreakAllNodeLinks();
}

void UK2BeamNode_WaitAll::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);

	if (!Context->bIsDebugging)
	{
		static auto WaitAllNodeName = FName("WaitAllNode");
		const auto WaitAllNodeNameStr = LOCTEXT("WaitAllNode", "Wait All Node");

		FToolMenuSection& Section = Menu->AddSection(WaitAllNodeName, WaitAllNodeNameStr);

		if (Context->Pin != nullptr)
		{
			if (CanRemovePin(Context->Pin))
			{
				Section.AddMenuEntry(
					"RemovePin",
					LOCTEXT("RemovePin", "Remove Pin"),
					LOCTEXT("RemovePinTooltip", "Remove this input pin"),
					FSlateIcon(),
					FUIAction(
						FExecuteAction::CreateUObject(const_cast<UK2BeamNode_WaitAll*>(this), &UK2BeamNode_WaitAll::RemoveInputPin, const_cast<UEdGraphPin*>(Context->Pin))
					)
				);
			}
		}
		else if (CanAddPin())
		{
			Section.AddMenuEntry(
				"AddPin",
				LOCTEXT("AddPin", "Add Pin"),
				LOCTEXT("AddPinTooltip", "Add another input pin"),
				FSlateIcon(),
				FUIAction(
					FExecuteAction::CreateUObject(const_cast<UK2BeamNode_WaitAll*>(this), &UK2BeamNode_WaitAll::AddInputPin)
				)
			);
		}
	}
}

void UK2BeamNode_WaitAll::PropagatePinType(UEdGraphPin* const& Pin) const
{
	// If it's a wildcard pin that was changed.
	if (Pin && Pin->ParentPin == nullptr)
	{
		const auto bIsConnected = Pin->LinkedTo.Num() > 0;
		if (bIsConnected)
		{
			const auto bIsWildcard = (Pin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard);
			if (bIsWildcard)
			{
				const auto& NewType = Pin->LinkedTo[0]->PinType;
				// If the connected pin is a FBeamWaitHandle, FBeamRequestContext or a FBeamOperationHandle struct, we propagate the type of that pin.
				if (NewType.PinSubCategoryObject == FBeamWaitHandle::StaticStruct() ||
					NewType.PinSubCategoryObject == FBeamOperationHandle::StaticStruct() ||
					NewType.PinSubCategoryObject == FBeamRequestContext::StaticStruct())
				{
					Pin->PinType = NewType;
					Pin->PinType.bIsReference = false;
					GetGraph()->NotifyGraphChanged();
				}
				else
				{
					FNotificationInfo Notification(LOCTEXT("UnsupportedWaitHandleDependencyType_Error",
					                                       "Unsupported WaitHandle Dependency type! Only supported types are: FBeamWaitHandle, FBeamRequestContext and FBeamOperationHandle."));
					Notification.bUseSuccessFailIcons = true;
					Notification.bFireAndForget = true;
					Notification.ExpireDuration = 7;
					Notification.bUseLargeFont = true;
					Notification.FadeInDuration = 1.0f;
					Notification.FadeOutDuration = 1.0f;
					//How long our Notification widget is, I believe this is in pixels.
					Notification.WidthOverride = 500.0f;
					FSlateNotificationManager::Get().AddNotification(Notification);

					Pin->BreakAllPinLinks();
				}
			}
		}
		else
		{
			if (Pin->LinkedTo.Num() == 0)
			{
				Pin->PinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
				Pin->PinType.PinSubCategory = NAME_None;
				Pin->PinType.PinSubCategoryObject = nullptr;
			}
		}
	}
}

void UK2BeamNode_WaitAll::CreateBeamFlowModePins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, P_CompleteCallback);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FBeamWaitCompleteEvent::StaticStruct(), P_Evt);	
}

void UK2BeamNode_WaitAll::EnterBeamFlowModeImpl()
{
	RemoveAllPins(this, {P_CompleteCallback});
	CreateBeamFlowModePins();
}

void UK2BeamNode_WaitAll::ExitBeamFlowModeImpl()
{
	const auto WaitAll = FindFunctionByName<UBeamBackend>(WaitAllFunctionName);
	RemoveAllPins(this, {P_CompleteCallback, P_Evt});
	ParseFunctionForNodeInputPins(this, WaitAll, {P_CompleteCallback}, true);
}

#undef LOCTEXT_NAMESPACE
