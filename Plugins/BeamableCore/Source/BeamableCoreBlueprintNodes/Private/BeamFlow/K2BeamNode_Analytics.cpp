// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_Analytics.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "SourceCodeNavigation.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_Analytics"

void UK2BeamNode_Analytics::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

void UK2BeamNode_Analytics::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);

	if (!Context->bIsDebugging)
	{
		FToolMenuSection& Section = Menu->AddSection("UK2BeamNode_Switch", NSLOCTEXT("K2Nodes", "UK2BeamNode_SwitchHeader", "Switch Node"));


		if (Context->Pin != NULL)
		{
			if (Context->Pin->Direction == EGPD_Input && Context->Pin->PinFriendlyName.ToString().StartsWith("Event Params"))
			{
				Section.AddMenuEntry(
					"RemovePin",
					LOCTEXT("RemovePin", "Remove element pin"),
					LOCTEXT("RemovePinTooltip", "Remove this element pin"),
					FSlateIcon(),
					FUIAction(
						FExecuteAction::CreateUObject(const_cast<UK2BeamNode_Analytics*>(this), &UK2BeamNode_Analytics::RemoveInputPin, const_cast<UEdGraphPin*>(Context->Pin))
					)
				);
			}
		}
	}
}

void UK2BeamNode_Analytics::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	const auto ExecPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	ExecPin->PinFriendlyName = FText::FromName(UEdGraphSchema_K2::PC_Exec);

	const auto OperationFunction = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());
	auto ReturnProperty = OperationFunction->GetReturnProperty();

	if (ReturnProperty != nullptr && ReturnProperty->IsA(FBoolProperty::StaticClass()))
	{
		auto SuccessPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, GetSuccessPinName());
		SuccessPin->PinFriendlyName = FText::FromName(GetSuccessPinName());
		auto FailurePin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, GetFailurePinName());
		FailurePin->PinFriendlyName = FText::FromName(GetFailurePinName());
	}
	else
	{
		auto Then = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
		Then->PinFriendlyName = FText::FromName(UEdGraphSchema_K2::PN_Then);
	}

	BeamK2::ParseFunctionForNodePins(this, OperationFunction, WrappedOperationFunctionInputPinNames, WrappedOperationFunctionOutputPinNames, GetIgnoredPinPredicate());

	if (bShowAsArray)
	{
		return;
	}

	for (auto Pin : Pins)
	{
		if (Pin->PinName.ToString().Contains("EventParams"))
		{
			WrappedOperationFunctionInputPinNames.Remove(Pin->GetName());
			Pins.Remove(Pin);
			break;
		}
	}

	// Recreate the additional EventParams pins
	FProperty* EventParamsElementProperty = nullptr;
	for (TFieldIterator<FProperty> PropIt(OperationFunction); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt)
	{
		if (PropIt->GetName() == TEXT("EventParams"))
		{
			if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*PropIt))
			{
				EventParamsElementProperty = ArrayProperty->Inner;
			}
			break;
		}
	}

	for (const FString& PinNameStr : AdditionalInputsNames)
	{
		const FName PinName = FName(*PinNameStr);
		UEdGraphPin* NewPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, PinName);

		int32 Index = AdditionalInputsNames.IndexOfByKey(PinNameStr);
		NewPin->PinFriendlyName = FText::FromString(FString::Printf(TEXT("Event Params %d"), Index));

		if (EventParamsElementProperty)
		{
			const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
			K2Schema->ConvertPropertyToPinType(EventParamsElementProperty, NewPin->PinType);
		}
	}
}
#if WITH_EDITOR
void UK2BeamNode_Analytics::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UK2BeamNode_Analytics, bShowAsArray))
	{
		ReconstructNode();
	}
}
#endif
void UK2BeamNode_Analytics::AddInputPin()
{
	FScopedTransaction Transaction(NSLOCTEXT("Kismet", "AddPin", "Add Pin"));
	Modify();

	const FString PinNameStr = FGuid::NewGuid().ToString();
	const FName PinName = FName(*PinNameStr);

	const auto OperationFunction = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());
	FProperty* EventParamsElementProperty = nullptr;

	for (TFieldIterator<FProperty> PropIt(OperationFunction); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt)
	{
		FProperty* Param = *PropIt;
		if (Param->GetName() == TEXT("EventParams"))
		{
			if (FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Param))
			{
				EventParamsElementProperty = ArrayProperty->Inner;
			}
			break;
		}
	}

	UEdGraphPin* NewPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, PinName);
	NewPin->PinFriendlyName = FText::FromString(FString::Printf(TEXT("Event Params %d"), AdditionalInputsNames.Num()));

	if (EventParamsElementProperty)
	{
		const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
		K2Schema->ConvertPropertyToPinType(EventParamsElementProperty, NewPin->PinType);
	}

	AdditionalInputsNames.Add(PinNameStr);

	FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
}


bool UK2BeamNode_Analytics::CanAddPin() const
{
	return !bShowAsArray;
}

bool UK2BeamNode_Analytics::CanRemovePin(const UEdGraphPin* Pin) const
{
	return Pin && Pin->PinFriendlyName.ToString().Contains("Event Params");
}

void UK2BeamNode_Analytics::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);
}


void UK2BeamNode_Analytics::RemoveInputPin(UEdGraphPin* Pin)
{
	if (Pin && CanRemovePin(Pin))
	{
		FScopedTransaction Transaction(NSLOCTEXT("Kismet", "RemovePin", "Remove Pin"));
		Modify();

		AdditionalInputsNames.Remove(Pin->GetName());
		Pins.Remove(Pin);

		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	}
}


FSlateIcon UK2BeamNode_Analytics::GetIconAndTint(FLinearColor& OutColor) const
{
	Super::GetIconAndTint(OutColor);
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_Analytics::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

FString UK2BeamNode_Analytics::GetPinMetaData(FName InPinName, FName InKey)
{
	FString MetaData = Super::GetPinMetaData(InPinName, InKey);

	// If there's no metadata directly on the pin then check for metadata on the function
	if (MetaData.IsEmpty())
	{
		return BeamK2::GetPinMetaData(InPinName, InKey, GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName()));
	}

	return MetaData;
}

void UK2BeamNode_Analytics::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	FString PinMetaData = GetPinMetaData(Pin->PinName, FName(BeamK2::MD_BeamCastTypeName));
	if (!PinMetaData.IsEmpty())
	{
		Super::PinDefaultValueChanged(Pin);
		if (Pin->LinkedTo.Num() == 0)
		{
			UClass* StaticClassType = Cast<UClass>(Pin->DefaultObject.Get());

			FString ClassPath = FSoftClassPath{StaticClassType}.GetAssetPath().ToString();
			NodeMetaData.Add(BeamK2::MD_BeamCastTypeName, *ClassPath);
			ReconstructNode();
		}
	}
	else
	{
		Super::PinDefaultValueChanged(Pin);
	}
}

void UK2BeamNode_Analytics::NodeConnectionListChanged()
{
	bool ShouldReconstructNode = false;
	for (auto Pin : Pins)
	{
		FString PinMetaData = GetPinMetaData(Pin->PinName, FName(BeamK2::MD_BeamCastTypeName));
		if (!PinMetaData.IsEmpty())
		{
			if (Pin->LinkedTo.Num() > 0)
			{
				if (NodeMetaData.Contains(BeamK2::MD_BeamCastTypeName))
				{
					NodeMetaData.Remove(BeamK2::MD_BeamCastTypeName);
					ShouldReconstructNode = true;
				}
			}
		}
	}
	if (ShouldReconstructNode)
	{
		ReconstructNode();
	}

	Super::NodeConnectionListChanged();
}

void UK2BeamNode_Analytics::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();


	// Get the UFunction reference to extract the parameters
	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	const UK2Node_CallFunction* CallGetSubsystem = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetSubsystemSelfFunctionName(), GetRuntimeSubsystemClass());
	const UK2Node_CallFunction* CallFunction = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetFunctionName(), GetRuntimeSubsystemClass());

	// Collect all EventParams pins and merge into array
	TArray<UEdGraphPin*> EventParamsPins;
	for (auto Pin : Pins)
	{
		if (Pin->PinFriendlyName.ToString().Contains("Event Params"))
		{
			EventParamsPins.Add(Pin);
		}
	}

	if (EventParamsPins.Num() > 0 && !bShowAsArray)
	{
		UK2Node_MakeArray* MakeArrayNode = CompilerContext.SpawnIntermediateNode<UK2Node_MakeArray>(this, SourceGraph);
		MakeArrayNode->NumInputs = EventParamsPins.Num();
		MakeArrayNode->AllocateDefaultPins();

		UEdGraphPin* ArrayOutputPin = MakeArrayNode->GetOutputPin();
		UEdGraphPin* EventParamsInputPin = CallFunction->FindPin(TEXT("EventParams"));
		if (EventParamsInputPin)
		{
			K2Schema->TryCreateConnection(ArrayOutputPin, EventParamsInputPin);
		}

		for (int32 i = 0; i < EventParamsPins.Num(); i++)
		{
			UEdGraphPin* ArrayInputPin = MakeArrayNode->FindPin(FString::Printf(TEXT("[%d]"), i));

			if (EventParamsPins[i]->LinkedTo.Num() > 0)
			{
				// Get the connected type
				UEdGraphPin* ConnectedPin = EventParamsPins[i]->LinkedTo[0];
				UScriptStruct* StructType = Cast<UScriptStruct>(ConnectedPin->PinType.PinSubCategoryObject.Get());

				if (StructType)
				{
					// Create a cast node to convert to UStruct*
					UK2Node_DynamicCast* CastNode = CompilerContext.SpawnIntermediateNode<UK2Node_DynamicCast>(this, SourceGraph);
					CastNode->TargetType = UStruct::StaticClass();
					CastNode->SetPurity(true);
					CastNode->AllocateDefaultPins();

					// Connect the source to the cast node
					UEdGraphPin* CastSourcePin = CastNode->GetCastSourcePin();
					CompilerContext.MovePinLinksToIntermediate(*EventParamsPins[i], *CastSourcePin);

					// Connect the cast result to the array input
					UEdGraphPin* CastResultPin = CastNode->GetCastResultPin();
					K2Schema->TryCreateConnection(CastResultPin, ArrayInputPin);
				}
				else
				{
					// Fallback if not a struct type
					CompilerContext.MovePinLinksToIntermediate(*EventParamsPins[i], *ArrayInputPin);
				}
			}else
			{
				CompilerContext.MovePinLinksToIntermediate(*EventParamsPins[i], *ArrayInputPin);
			}
		}
	}

	// Connects the result of the "static BeamApi::GetSelf" call to the "non-static RuntimeSubsystem::___function" Call Function node.
	BeamK2::SetUpPinsFunctionToOwnerSubsystem(CallGetSubsystem, CallFunction);

	// Create the link to the node to the call function execute pin
	if (CallFunction->GetExecPin())
	{
		CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CallFunction->GetExecPin());
	}
	else
	{
		CompilerContext.MessageLog.Error(TEXT("This node cannot work when the underlying function is a Blueprint Pure function."));
		return;
	}

	UEdGraphPin* ExecutePin = nullptr;
	// If the return type is a boolean we create the connections required to have a valid/invalid path
	auto ReturnProperty = Function->GetReturnProperty();
	if (ReturnProperty != nullptr && ReturnProperty->IsA(FBoolProperty::StaticClass()))
	{
		// If the function contains the ReturnValue in the ExpandBoolAsExec we only need to connect the True and False outputs with the valid/invalid custom outputs.
		if (Function->GetMetaData("ExpandBoolAsExecs").Contains("ReturnValue"))
		{
			CompilerContext.MovePinLinksToIntermediate(*FindPin(GetSuccessPinName()), *CallFunction->FindPin(TEXT("True")));
			CompilerContext.MovePinLinksToIntermediate(*FindPin(GetFailurePinName()), *CallFunction->FindPin(TEXT("False")));
		}
		else
		{
			// In the case of it don't have we create the branch internally to make the boolean output as a valid/invalid output
			UK2Node_IfThenElse* IfThenElseNode = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>(this, SourceGraph);
			IfThenElseNode->AllocateDefaultPins();

			CompilerContext.GetSchema()->TryCreateConnection(CallFunction->GetThenPin(), IfThenElseNode->GetExecPin());
			CompilerContext.GetSchema()->TryCreateConnection(CallFunction->GetReturnValuePin(), IfThenElseNode->GetConditionPin());

			CompilerContext.MovePinLinksToIntermediate(*FindPin(GetSuccessPinName()), *IfThenElseNode->GetThenPin());
			CompilerContext.MovePinLinksToIntermediate(*FindPin(GetFailurePinName()), *IfThenElseNode->GetElsePin());
		}
	}
	else
	{
		// If the return type is not a boolean we just have the then pin.
		CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *CallFunction->GetThenPin());
	}

	// Connect the input pins from the custom node to the intermediate call functions
	for (auto InputPinName : WrappedOperationFunctionInputPinNames)
	{
		if (InputPinName.StartsWith("EventParams_"))
		{
			continue; // Skip EventParams pins as they are handled separately
		}
		CompilerContext.MovePinLinksToIntermediate(*FindPin(FName(*InputPinName)), *CallFunction->FindPin(FName(*InputPinName)));
	}
	// Connect the output pins from the custom node to the intermediate call functions
	for (auto OutputPinName : WrappedOperationFunctionOutputPinNames)
	{
		UEdGraphPin* OutputPin = FindPin(FName(*OutputPinName));
		UEdGraphPin* CallFunctionOutputPin = CallFunction->FindPin(FName(*OutputPinName));

		if (OutputPin->PinType != CallFunctionOutputPin->PinType)
		{
			// Create the cast node 
			UClass* StaticClassType = Cast<UClass>(OutputPin->PinType.PinSubCategoryObject.Get());
			if (StaticClassType)
			{
				auto CastNode = BeamK2::CreateDynamicCastNode(this, CompilerContext, SourceGraph, StaticClassType, true);

				K2Schema->TryCreateConnection(CastNode->GetCastSourcePin(), CallFunctionOutputPin);

				const auto SuccessFlowCastObject = CompilerContext.MovePinLinksToIntermediate(*OutputPin, *CastNode->GetCastResultPin());
				check(!SuccessFlowCastObject.IsFatal());
			}
			else
			{
				CompilerContext.MovePinLinksToIntermediate(*OutputPin, *CallFunctionOutputPin);
			}
		}
		else
		{
			CompilerContext.MovePinLinksToIntermediate(*OutputPin, *CallFunctionOutputPin);
		}
	}


	// Break original links
	BreakAllNodeLinks();
}

void UK2BeamNode_Analytics::JumpToDefinition() const
{
	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	if (!Function) return;

	FSourceCodeNavigation::NavigateToFunction(Function);
}

FName UK2BeamNode_Analytics::GetSubsystemSelfFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

FName UK2BeamNode_Analytics::GetFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

UClass* UK2BeamNode_Analytics::GetRuntimeSubsystemClass() const
{
	return UClass::StaticClass();
}

BeamK2::CheckParamIsValidForNodePredicate UK2BeamNode_Analytics::GetIgnoredPinPredicate() const
{
	return IsIgnoredPinOfReturnBoolType;
}


bool UK2BeamNode_Analytics::IsIgnoredPinOfReturnBoolType(const UEdGraphNode* EdGraphNode, const FProperty* Param)
{
	// We will be treating bool return types in a different way
	const bool bIsReturnType = Param->GetName() == TEXT("ReturnValue") && Param->IsA(FBoolProperty::StaticClass());

	// We also ignore duplicated pin names. This is by design for now 
	const UEdGraphPin* EdGraphPin = EdGraphNode->FindPin(Param->GetFName());

	// if its return true the output is valid what means that is not a boolean return value.
	return EdGraphPin || bIsReturnType;
}

#undef LOCTEXT_NAMESPACE
