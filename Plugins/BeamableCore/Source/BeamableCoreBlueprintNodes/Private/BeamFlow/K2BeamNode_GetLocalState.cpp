// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_GetLocalState.h"

#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "SourceCodeNavigation.h"

void UK2BeamNode_GetLocalState::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

void UK2BeamNode_GetLocalState::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	// Create the input execution flow pin
	const auto ExecPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	ExecPin->PinFriendlyName = FText::FromName(UEdGraphSchema_K2::PC_Exec);

	const auto OperationFunction = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	auto ReturnProperty = OperationFunction->GetReturnProperty();

	// Create the output exec for different cases, if the return type is a boolean then we return it as a valid and invalid execute to prevent the usage of branch
	// If the return is not a boolean we just have the then execute output
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

	//Create all the pins (input/output) for the function
	BeamK2::ParseFunctionForNodePins(this, OperationFunction, WrappedOperationFunctionInputPinNames, WrappedOperationFunctionOutputPinNames, GetIgnoredPinPredicate());
}


FSlateIcon UK2BeamNode_GetLocalState::GetIconAndTint(FLinearColor& OutColor) const
{
	Super::GetIconAndTint(OutColor);
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_GetLocalState::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

void UK2BeamNode_GetLocalState::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Get the UFunction reference to extract the parameters
	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	const UK2Node_CallFunction* CallGetSubsystem = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetSubsystemSelfFunctionName(), GetRuntimeSubsystemClass());
	const UK2Node_CallFunction* CallFunction = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetFunctionName(), GetRuntimeSubsystemClass());


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
		CompilerContext.MovePinLinksToIntermediate(*FindPin(FName(*InputPinName)), *CallFunction->FindPin(FName(*InputPinName)));
	}
	// Connect the output pins from the custom node to the intermediate call functions
	for (auto OutputPinName : WrappedOperationFunctionOutputPinNames)
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPin(FName(*OutputPinName)), *CallFunction->FindPin(FName(*OutputPinName)));
	}


	// Break original links
	BreakAllNodeLinks();
}

void UK2BeamNode_GetLocalState::JumpToDefinition() const
{
	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	if (!Function) return;

	FSourceCodeNavigation::NavigateToFunction(Function);
}

FName UK2BeamNode_GetLocalState::GetSubsystemSelfFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

FName UK2BeamNode_GetLocalState::GetFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

UClass* UK2BeamNode_GetLocalState::GetRuntimeSubsystemClass() const
{
	return UClass::StaticClass();
}

BeamK2::CheckParamIsValidForNodePredicate UK2BeamNode_GetLocalState::GetIgnoredPinPredicate() const
{
	return IsIgnoredPinOfReturnBoolType;
}


bool UK2BeamNode_GetLocalState::IsIgnoredPinOfReturnBoolType(const UEdGraphNode* EdGraphNode, const FProperty* Param)
{
	// We will be treating bool return types in a different way
	const bool bIsReturnType = Param->GetName() == TEXT("ReturnValue") && Param->IsA(FBoolProperty::StaticClass());

	// We also ignore duplicated pin names. This is by design for now 
	const UEdGraphPin* EdGraphPin = EdGraphNode->FindPin(Param->GetFName());

	// if its return true the output is valid what means that is not a boolean return value.
	return EdGraphPin || bIsReturnType;
}
