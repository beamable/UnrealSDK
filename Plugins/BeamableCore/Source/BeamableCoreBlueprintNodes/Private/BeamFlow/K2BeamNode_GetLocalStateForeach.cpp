// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_GetLocalStateForeach.h"

#include "BeamK2.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_AssignmentStatement.h"
#include "K2Node_CallFunction.h"
#include "K2Node_ExecutionSequence.h"
#include "K2Node_IfThenElse.h"
#include "K2Node_TemporaryVariable.h"
#include "KismetCompiler.h"
#include "SourceCodeNavigation.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#define LOCTEXT_NAMESPACE "BeamK2_GetLocalStateForeach"


void UK2BeamNode_GetLocalStateForeach::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	const UEdGraphSchema_K2* Schema = GetDefault<UEdGraphSchema_K2>();

	// Create the exec input pin
	auto ExecPin = CreatePin(EGPD_Input, Schema->PC_Exec, UEdGraphSchema_K2::PN_Execute);
	ExecPin->PinFriendlyName = FText::FromName(UEdGraphSchema_K2::PC_Exec);

	CreatePin(EGPD_Output, Schema->PC_Exec, GetLoopBodyName());

	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	// Generate all pins that is not an array output
	BeamK2::ParseFunctionForNodePins(this, Function, WrappedOperationFunctionInputPinNames, WrappedOperationFunctionOutputPinNames, GetIgnoredPinPredicate());

	//Create only the array element as the output
	BeamK2::ParseFunctionForNodeOutputPinsArrayElement(this, Function, WrappedOperationFunctionOutputPinArrayNames);

	CreatePin(EGPD_Input, Schema->PC_Exec, GetBreakPinName());

	CreatePin(EGPD_Output, Schema->PC_Int, GetArrayIndexPinName());

	CreatePin(EGPD_Output, Schema->PC_Exec, GetCompletedPinName());

	// If the user would like to see the arrays outputs it's possible using this property
	if (bShowRawArrayMode)
	{
		TArray<FString> InputArray = TArray<FString>();
		TArray<FString> OutputArray = TArray<FString>();
		BeamK2::ParseFunctionForNodePins(this, Function, InputArray, OutputArray, IsIgnoredPinOfReturnNonArrayType);
		for (const auto& Output : OutputArray)
		{
			WrappedOperationFunctionOutputPinNames.Add(Output);
		}
	}
}


FSlateIcon UK2BeamNode_GetLocalStateForeach::GetIconAndTint(FLinearColor& OutColor) const
{
	const auto Icon = Super::GetIconAndTint(OutColor);
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_GetLocalStateForeach::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

void UK2BeamNode_GetLocalStateForeach::JumpToDefinition() const
{
	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	if (!Function) return;

	FSourceCodeNavigation::NavigateToFunction(Function);
}

void UK2BeamNode_GetLocalStateForeach::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	const auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());

	auto ReturnProperty = Function->GetReturnProperty();

	const auto K2Schema = GetDefault<UEdGraphSchema_K2>();

	const UK2Node_CallFunction* CallGetSubsystem = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetSubsystemSelfFunctionName(), GetRuntimeSubsystemClass());
	const UK2Node_CallFunction* CallFunction = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetFunctionName(), GetRuntimeSubsystemClass());


	// Connects the result of the "static BeamApi::GetSelf" call to the "non-static RuntimeSubsystem::___function" Call Function node.
	BeamK2::SetUpPinsFunctionToOwnerSubsystem(CallGetSubsystem, CallFunction);

	// Create the link to the node to the call function execute pin
	CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CallFunction->GetExecPin());

	// Connect the input pins from the custom node to the intermediate call functions
	for (const auto& InputPinName : WrappedOperationFunctionInputPinNames)
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPin(FName(*InputPinName)), *CallFunction->FindPin(FName(*InputPinName)));
	}

	// Connect the output pins from the custom node to the intermediate call functions
	for (const auto& OutputPinName : WrappedOperationFunctionOutputPinNames)
	{
		CompilerContext.MovePinLinksToIntermediate(*FindPin(FName(*OutputPinName)), *CallFunction->FindPin(FName(*OutputPinName)));
	}

	// Cache all our important pins
	const auto ForEachPin = GetForEachPin();
	const auto ArrayIndexPin = GetArrayIndexPin();
	const auto CompletedPin = GetCompletedPin();
	const auto BreakPin = GetBreakPin();

	// Create a loop counter variable
	const auto CreateTemporaryVariable = CompilerContext.SpawnIntermediateNode<UK2Node_TemporaryVariable>(this, SourceGraph);
	CreateTemporaryVariable->VariableType.PinCategory = UEdGraphSchema_K2::PC_Int;
	CreateTemporaryVariable->AllocateDefaultPins();

	const auto Temp_Variable = CreateTemporaryVariable->GetVariablePin();
	CompilerContext.MovePinLinksToIntermediate(*ArrayIndexPin, *Temp_Variable);

	// Initialize the temporary to 0
	const auto InitTemporaryVariable = CompilerContext.SpawnIntermediateNode<UK2Node_AssignmentStatement>(this, SourceGraph);
	InitTemporaryVariable->AllocateDefaultPins();

	const auto Init_Exec = InitTemporaryVariable->GetExecPin();
	const auto Init_Variable = InitTemporaryVariable->GetVariablePin();
	const auto Init_Value = InitTemporaryVariable->GetValuePin();
	const auto Init_Then = InitTemporaryVariable->GetThenPin();

	// Connect the function result with the init of the foreach
	if (ReturnProperty != nullptr && ReturnProperty->IsA(FBoolProperty::StaticClass()) && Function->GetMetaData("ExpandBoolAsExecs").Contains("ReturnValue"))
	{
		K2Schema->TryCreateConnection(CallFunction->FindPin(FName("True")), Init_Exec);
		K2Schema->TryCreateConnection(CallFunction->FindPin(FName("False")), Init_Exec);
	}
	else
	{
		K2Schema->TryCreateConnection(CallFunction->GetThenPin(), Init_Exec);
	}

	K2Schema->TryCreateConnection(Init_Variable, Temp_Variable);
	Init_Value->DefaultValue = TEXT("0");

	// Branch on comparing the loop index with the length of the array
	const auto BranchOnIndex = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>(this, SourceGraph);
	BranchOnIndex->AllocateDefaultPins();

	const auto Branch_Exec = BranchOnIndex->GetExecPin();
	const auto Branch_Input = BranchOnIndex->GetConditionPin();
	const auto Branch_Then = BranchOnIndex->GetThenPin();
	const auto Branch_Else = BranchOnIndex->GetElsePin();

	Init_Then->MakeLinkTo(Branch_Exec);
	CompilerContext.MovePinLinksToIntermediate(*CompletedPin, *Branch_Else);

	const auto CompareLessThan = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CompareLessThan->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UKismetMathLibrary, Less_IntInt), UKismetMathLibrary::StaticClass());
	CompareLessThan->AllocateDefaultPins();

	const auto Compare_A = CompareLessThan->FindPinChecked(TEXT("A"));
	const auto Compare_B = CompareLessThan->FindPinChecked(TEXT("B"));
	const auto Compare_Return = CompareLessThan->GetReturnValuePin();

	Branch_Input->MakeLinkTo(Compare_Return);
	Temp_Variable->MakeLinkTo(Compare_A);

	// Sequence the loop body and incrementing the loop counter
	const auto LoopSequence = CompilerContext.SpawnIntermediateNode<UK2Node_ExecutionSequence>(this, SourceGraph);
	LoopSequence->AllocateDefaultPins();

	const auto Sequence_Exec = LoopSequence->GetExecPin();
	const auto Sequence_One = LoopSequence->GetThenPinGivenIndex(0);
	const auto Sequence_Two = LoopSequence->GetThenPinGivenIndex(1);

	Branch_Then->MakeLinkTo(Sequence_Exec);
	CompilerContext.MovePinLinksToIntermediate(*ForEachPin, *Sequence_One);

	// Increment the loop counter by one
	const auto IncrementVariable = CompilerContext.SpawnIntermediateNode<UK2Node_AssignmentStatement>(this, SourceGraph);
	IncrementVariable->AllocateDefaultPins();

	const auto Inc_Exec = IncrementVariable->GetExecPin();
	const auto Inc_Variable = IncrementVariable->GetVariablePin();
	const auto Inc_Value = IncrementVariable->GetValuePin();
	const auto Inc_Then = IncrementVariable->GetThenPin();

	Sequence_Two->MakeLinkTo(Inc_Exec);
	Branch_Exec->MakeLinkTo(Inc_Then);
	K2Schema->TryCreateConnection(Temp_Variable, Inc_Variable);

	const auto AddOne = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	AddOne->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UKismetMathLibrary, Add_IntInt), UKismetMathLibrary::StaticClass());
	AddOne->AllocateDefaultPins();

	const auto Add_A = AddOne->FindPinChecked(TEXT("A"));
	const auto Add_B = AddOne->FindPinChecked(TEXT("B"));
	const auto Add_Return = AddOne->GetReturnValuePin();

	Temp_Variable->MakeLinkTo(Add_A);
	Add_B->DefaultValue = TEXT("1");
	Add_Return->MakeLinkTo(Inc_Value);

	// Set the break pin to set the index to the length size making the condition fail and the for loop end
	const auto SetVariable = CompilerContext.SpawnIntermediateNode<UK2Node_AssignmentStatement>(this, SourceGraph);
	SetVariable->AllocateDefaultPins();

	const auto Set_Exec = SetVariable->GetExecPin();
	const auto Set_Variable = SetVariable->GetVariablePin();
	const auto Set_Value = SetVariable->GetValuePin();

	CompilerContext.MovePinLinksToIntermediate(*BreakPin, *Set_Exec);
	K2Schema->TryCreateConnection(Temp_Variable, Set_Variable);

	// That will used to connect the end of the chain of Max Length operation to the result node
	UEdGraphPin* MaxLengthPin = nullptr;

	// Coerce the wildcard pin types
	for (const auto& OutputPinArrayName : WrappedOperationFunctionOutputPinArrayNames)
	{
		const auto ArrayPin = CallFunction->FindPinChecked(OutputPinArrayName);
		ArrayPin->Direction = EGPD_Output;

		// Spawn a length node per array output
		const auto GetArrayLength = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
		GetArrayLength->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UKismetArrayLibrary, Array_Length), UKismetArrayLibrary::StaticClass());
		GetArrayLength->AllocateDefaultPins();

		const auto ArrayLength_Array = GetArrayLength->FindPinChecked(TEXT("TargetArray"));
		const auto ArrayLength_Return = GetArrayLength->GetReturnValuePin();
		ArrayLength_Array->PinType = ArrayPin->PinType;
		K2Schema->TryCreateConnection(ArrayPin, ArrayLength_Array);

		// Spawn a max to get the greater length
		UK2Node_CallFunction* MaxNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
		MaxNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UKismetMathLibrary, Max), UKismetMathLibrary::StaticClass());
		MaxNode->AllocateDefaultPins();

		UEdGraphPin* A = MaxNode->FindPinChecked(TEXT("A"));
		UEdGraphPin* B = MaxNode->FindPinChecked(TEXT("B"));
		UEdGraphPin* ReturnValue = MaxNode->GetReturnValuePin();

		K2Schema->TryCreateConnection(ArrayLength_Return, A);

		if (MaxLengthPin == nullptr)
		{
			B->DefaultValue = TEXT("0");
		}
		else
		{
			MaxLengthPin->MakeLinkTo(B);
		}

		MaxLengthPin = ReturnValue;

		// Get the array last index to Min(A, B) with the current index
		const auto GetArrayLastIndex = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
		GetArrayLastIndex->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UKismetArrayLibrary, Array_LastIndex), UKismetArrayLibrary::StaticClass());
		GetArrayLastIndex->AllocateDefaultPins();

		const auto ArrayLastIndex_Array = GetArrayLastIndex->FindPinChecked(TEXT("TargetArray"));
		const auto ArrayLastIndex_Return = GetArrayLastIndex->GetReturnValuePin();

		ArrayLastIndex_Array->PinType = ArrayPin->PinType;
		K2Schema->TryCreateConnection(ArrayPin, ArrayLastIndex_Array);

		// Spawn the min node to compare the current index with the last index array
		UK2Node_CallFunction* MinNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
		MinNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UKismetMathLibrary, Min), UKismetMathLibrary::StaticClass());
		MinNode->AllocateDefaultPins();

		UEdGraphPin* Min_A = MinNode->FindPinChecked(TEXT("A"));
		UEdGraphPin* Min_B = MinNode->FindPinChecked(TEXT("B"));
		UEdGraphPin* Min_ReturnValue = MinNode->GetReturnValuePin();

		K2Schema->TryCreateConnection(ArrayLastIndex_Return, Min_A);
		K2Schema->TryCreateConnection(Temp_Variable, Min_B);

		// Get element from the array using the index
		const auto GetArrayElement = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
		GetArrayElement->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UKismetArrayLibrary, Array_Get), UKismetArrayLibrary::StaticClass());
		GetArrayElement->AllocateDefaultPins();

		const auto GetElement_Array = GetArrayElement->FindPinChecked(TEXT("TargetArray"));
		const auto GetElement_Index = GetArrayElement->FindPinChecked(TEXT("Index"));
		const auto GetElement_Return = GetArrayElement->FindPinChecked(TEXT("Item"));

		// The element pin have the same name as the array +Element 
		auto ElementPin = FindPinChecked(OutputPinArrayName + "Element");
		GetElement_Return->PinType = ElementPin->PinType;
		CompilerContext.MovePinLinksToIntermediate(*ElementPin, *GetElement_Return);

		GetElement_Index->MakeLinkTo(Min_ReturnValue);

		GetElement_Array->PinType = ArrayPin->PinType;
		K2Schema->TryCreateConnection(ArrayPin, GetElement_Array);
	}

	//MaxLength only works out of the for loop
	Compare_B->MakeLinkTo(MaxLengthPin);

	MaxLengthPin->MakeLinkTo(Set_Value);

	BreakAllNodeLinks();
}

void UK2BeamNode_GetLocalStateForeach::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

void UK2BeamNode_GetLocalStateForeach::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const auto FlowPropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_GetLocalStateForeach, bShowRawArrayMode);
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetNameCPP().Equals(FlowPropName.ToString()))
	{
		ReconstructNode();
	}
}


UEdGraphPin* UK2BeamNode_GetLocalStateForeach::GetArrayPin()
{
	return FindPinChecked(GetArrayPinName());
}

UEdGraphPin* UK2BeamNode_GetLocalStateForeach::GetBreakPin()
{
	return FindPinChecked(GetBreakPinName());
}

UEdGraphPin* UK2BeamNode_GetLocalStateForeach::GetForEachPin()
{
	return FindPinChecked(GetLoopBodyName());
}


UEdGraphPin* UK2BeamNode_GetLocalStateForeach::GetArrayIndexPin()
{
	return FindPinChecked(GetArrayIndexPinName());
}

UEdGraphPin* UK2BeamNode_GetLocalStateForeach::GetCompletedPin()
{
	return FindPinChecked(GetCompletedPinName());
}

FName UK2BeamNode_GetLocalStateForeach::GetSubsystemSelfFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

FName UK2BeamNode_GetLocalStateForeach::GetFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

UClass* UK2BeamNode_GetLocalStateForeach::GetRuntimeSubsystemClass() const
{
	return UClass::StaticClass();
}

BeamK2::CheckParamIsValidForNodePredicate UK2BeamNode_GetLocalStateForeach::GetIgnoredPinPredicate() const
{
	return IsIgnoredPinOfReturnArrayType;
}


bool UK2BeamNode_GetLocalStateForeach::IsIgnoredPinOfReturnArrayType(const UEdGraphNode* EdGraphNode, const FProperty* Param)
{
	// We will be treating array return types in a different way
	const bool bIsArrayReturnType = Param->IsA(FArrayProperty::StaticClass());

	const bool bIsOutputParam = !(!Param->HasAnyPropertyFlags(CPF_OutParm) || Param->HasAnyPropertyFlags(CPF_ReferenceParm));

	const bool bIsInvalidPin = bIsArrayReturnType && bIsOutputParam;

	// We also ignore duplicated pin names. This is by design for now 
	const UEdGraphPin* EdGraphPin = EdGraphNode->FindPin(Param->GetFName());

	// if its return true the output is valid what means that is not a boolean return value.
	return EdGraphPin || bIsInvalidPin;
}

bool UK2BeamNode_GetLocalStateForeach::IsIgnoredPinOfReturnNonArrayType(const UEdGraphNode* EdGraphNode, const FProperty* Param)
{
	// We will be treating array return types in a different way
	const bool bIsArrayReturnType = Param->IsA(FArrayProperty::StaticClass());

	const bool bIsOutputParam = !(!Param->HasAnyPropertyFlags(CPF_OutParm) || Param->HasAnyPropertyFlags(CPF_ReferenceParm));

	const bool bIsValidPin = bIsArrayReturnType && bIsOutputParam;

	return !bIsValidPin;
}

#undef LOCTEXT_NAMESPACE
