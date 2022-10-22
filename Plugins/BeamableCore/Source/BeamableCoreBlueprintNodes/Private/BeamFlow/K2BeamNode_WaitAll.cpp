// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_WaitAll.h"


#include "BeamK2.h"
#include "BeamFlow/ExecuteRequest/K2BeamNode_ApiRequest.h"

#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "K2Node_CreateDelegate.h"
#include "K2Node_MakeArray.h"
#include "ToolMenu.h"
#include "BeamBackend/BeamRequestWaitHandle.h"
#include "BeamBackend/BeamBackend.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Misc/DefaultValueHelper.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_WaitAll"


using namespace BeamK2;

const FName UK2BeamNode_WaitAll::SelfFunctionName = GET_FUNCTION_NAME_CHECKED(UBeamBackend, GetSelf);
const FName UK2BeamNode_WaitAll::WaitAllFunctionName = GET_FUNCTION_NAME_CHECKED(UBeamBackend, WaitAll);

const FName UK2BeamNode_WaitAll::P_CompleteCallback = FName("OnComplete");
const FName UK2BeamNode_WaitAll::P_Contexts = FName("Contexts");
const FName UK2BeamNode_WaitAll::P_Requests = FName("Requests");
const FName UK2BeamNode_WaitAll::P_Responses = FName("Responses");
const FName UK2BeamNode_WaitAll::P_Errors = FName("Errors");

FText UK2BeamNode_WaitAll::GetMenuCategory() const
{
	return LOCTEXT("BeamNodeCategory", "Beam|Flow");
}

FText UK2BeamNode_WaitAll::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("BeamNodeTitle", "Flow - Utils - Wait All");
}

void UK2BeamNode_WaitAll::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	// Create the input execution flow pin
	const auto _ = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

	// Create the output pins in an order that improves usability.
	const auto SynchronousFlowPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	const auto WaitHandle = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FBeamRequestWaitHandle::StaticStruct(), TEXT("WaitHandle"));
	SynchronousFlowPin->PinFriendlyName = LOCTEXT("BeamNode", "Synchronous Flow");
	WaitHandle->PinToolTip = TEXT("");

	for (int i = 0; i < NumPins; ++i)
		CreateContextInputPin(i);

	if (bIsInBeamFlowMode)
		CreateBeamFlowModePins();
	else
		ParseFunctionForNodeInputPins(this, FindFunctionByName<UBeamBackend>(WaitAllFunctionName), {P_CompleteCallback}, true);
}

UEdGraphPin* UK2BeamNode_WaitAll::CreateContextInputPin(const int32 PinIdx)
{
	const auto PinName = FName(FString::Printf(TEXT("Context - %d"), PinIdx));
	return CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FBeamRequestContext::StaticStruct(), PinName);
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
					LocalPin->PinName = FName(FString::Printf(TEXT("Context - %d"), PinNameIdx - 1));
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

void UK2BeamNode_WaitAll::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Create nodes calling the GetSelf method of the UBeamBackend and the WaitAll function
	const auto CallSelfNode = CreateCallFunctionNode(this, CompilerContext, SourceGraph, SelfFunctionName, UBeamBackend::StaticClass());
	const auto CallWaitAllNode = CreateCallFunctionNode(this, CompilerContext, SourceGraph, WaitAllFunctionName, UBeamBackend::StaticClass());

	// Link the CallSelf node to the CallWaitAll node
	const auto bConnectedSubsystemToFunctionCall = K2Schema->TryCreateConnection(CallSelfNode->GetReturnValuePin(), K2Schema->FindSelfPin(*CallWaitAllNode, EGPD_Input));
	check(bConnectedSubsystemToFunctionCall)

	// Gets a list of all input pins that are structs in this wrapper node.
	const auto AllInputPins = Pins.FilterByPredicate([](const UEdGraphPin* P)
	{
		return P->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct && P->Direction == EGPD_Input;
	});

	// Creates a make array node with the same amount of Struct pins as we have here.
	const auto MakeArrayNode = CreateMakeArrayNode(this, CompilerContext, SourceGraph, AllInputPins.Num());

	// Connect the output pin of the make array node to the input Contexts the WaitAll node requires
	const auto MakeArrayOutputPin = MakeArrayNode->GetOutputPin();
	const auto CallWaitAllContextPin = CallWaitAllNode->FindPin(P_Contexts);
	const auto bDidConnectMakeArrayResultPin = K2Schema->TryCreateConnection(MakeArrayOutputPin, CallWaitAllContextPin);
	check(bDidConnectMakeArrayResultPin)

	// Move all pins connected to the Context input pins in the wrapper node to the MakeArray intermediate node
	auto MakeArrayNodeInputPins = MakeArrayNode->Pins.FilterByPredicate([](const UEdGraphPin* P) { return P->Direction == EGPD_Input; });
	check(MakeArrayNode->NumInputs == AllInputPins.Num())
	for (int i = 0; i < MakeArrayNodeInputPins.Num(); ++i)
	{
		const auto bDidMoveInputPin = CompilerContext.MovePinLinksToIntermediate(*AllInputPins[i], *MakeArrayNodeInputPins[i]);
		check(!bDidMoveInputPin.IsFatal())
	}

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
		const auto ContextsPin = FindPinChecked(P_Contexts);
		const auto RequestsPin = FindPinChecked(P_Requests);
		const auto ResponsesPin = FindPinChecked(P_Responses);
		const auto ErrorsPin = FindPinChecked(P_Errors);

		const TArray<UEdGraphPin*> StartingGraphs{OnCompleteFlowPin,};
		const TArray<FName> RelevantEventSpawningFunctionNames{GET_FUNCTION_NAME_CHECKED(UBeamBackend, WaitAll)};
		TArray<TArray<UEdGraphNode*>> OutPerFlowNodes;
		TArray<TArray<UEdGraphNode*>> OutPerEventFlowNodes;
		GetPerBeamFlowNodes(CompilerContext, this, StartingGraphs, RelevantEventSpawningFunctionNames, OutPerFlowNodes, OutPerEventFlowNodes);

		const auto WaitAllOnCompletePin = CallWaitAllNode->FindPinChecked(P_CompleteCallback, EGPD_Input);

		const auto CompleteEventNodeExecPin = CompleteEventNode->FindPin(UEdGraphSchema_K2::PN_Then);
		const auto CompleteEventDelegatePin = CompleteEventNode->FindPinChecked(CompleteEventNode->DelegateOutputName);
		const auto CompleteEventContextsPin = CompleteEventNode->FindPinChecked(P_Contexts);
		const auto CompleteEventRequestsPin = CompleteEventNode->FindPinChecked(P_Requests);
		const auto CompleteEventResponsesPin = CompleteEventNode->FindPinChecked(P_Responses);
		const auto CompleteEventErrorsPin = CompleteEventNode->FindPinChecked(P_Errors);


		// Replace the connections of any of the nodes' pins with any matching pin in the first list with its corresponding pin in the second list.		
		const TArray<UEdGraphPin*> CompletePins{ContextsPin, RequestsPin, ResponsesPin, ErrorsPin};
		const TArray<UEdGraphPin*> CompleteEventPins{CompleteEventContextsPin, CompleteEventRequestsPin, CompleteEventResponsesPin, CompleteEventErrorsPin};
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

void UK2BeamNode_WaitAll::CreateBeamFlowModePins()
{
	FCreatePinParams PinParams;
	PinParams.ContainerType = EPinContainerType::Array;

	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, P_CompleteCallback);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FBeamRequestContext::StaticStruct(), P_Contexts, PinParams);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Interface, UBeamBaseRequestInterface::StaticClass(), P_Requests, PinParams);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), P_Responses, PinParams);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FBeamErrorResponse::StaticStruct(), P_Errors, PinParams);
}

void UK2BeamNode_WaitAll::EnterBeamFlowModeImpl()
{
	RemoveAllPins(this, {P_CompleteCallback});
	CreateBeamFlowModePins();
}

void UK2BeamNode_WaitAll::ExitBeamFlowModeImpl()
{
	const auto WaitAll = FindFunctionByName<UBeamBackend>(WaitAllFunctionName);
	RemoveAllPins(this, {P_CompleteCallback, P_Contexts, P_Requests, P_Responses, P_Errors});
	ParseFunctionForNodeInputPins(this, WaitAll, {P_CompleteCallback}, true);
}

#undef LOCTEXT_NAMESPACE
