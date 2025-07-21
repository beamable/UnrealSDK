// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_Switch.h"

#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"

void UK2BeamNode_Switch::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	const UEdGraphSchema_K2* Schema = GetDefault<UEdGraphSchema_K2>();

	// Create the input execution flow pin
	const auto ExecPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	ExecPin->PinFriendlyName = FText::FromName(UEdGraphSchema_K2::PC_Exec);

	const auto ThenPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	ThenPin->PinFriendlyName = FText::FromName(FName("Default Output - Then"));

	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, InputPinName);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, OutputPinName);

	TArray<FString> OutputDefaultValues;
	DefaultValue.GenerateValueArray(OutputDefaultValues);

	TArray<FName> OutputNamesKeys;
	DefaultValue.GetKeys(OutputNamesKeys);

	for (auto index = 0; index < OutputNamesKeys.Num(); ++index)
	{
		auto Pin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Class, UObject::StaticClass(), OutputNamesKeys[index]);
		Pin->bNotConnectable = true;
	}

	for (auto index = 0; index < OutputDefaultValues.Num(); ++index)
	{
		FString ClassName = OutputDefaultValues[index];

		if (ClassName.IsEmpty()) continue;

		UClass* MyClass = FindObject<UClass>(ANY_PACKAGE, *ClassName);

		if (!MyClass) continue;

		// Exec output
		CreatePin(EGPD_Output, Schema->PC_Exec, GetClassExecPinName(MyClass));

		// Casted output object
		CreatePin(EGPD_Output, Schema->PC_Object, MyClass, GetClassOutputPinName(MyClass));
	}
}

void UK2BeamNode_Switch::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	bool FirstCast = true;

	UEdGraphPin* InvalidCastPin = GetExecPin();

	UEdGraphPin* InputLinkPin = InputLinkPin = GetInputPin();

	if (GetInputPin()->LinkedTo.Num() > 0)
	{
		InputLinkPin = GetInputPin()->LinkedTo[0];
	}

	for (auto Pin : Pins)
	{
		// If is a class input then will have a default value set
		if (!DefaultValue.Contains(Pin->PinName))
		{
			continue;
		}

		FString ClassName = DefaultValue[Pin->PinName];

		if (!Pin || ClassName.IsEmpty()) continue;

		UClass* MyClass = FindObject<UClass>(ANY_PACKAGE, *ClassName);
		// Theres any class setup for this pin name then we create a cast for it
		if (!MyClass) continue;

		auto OutputObjectClassPin = FindPin(GetClassOutputPinName(MyClass));
		auto OutputExecuteClassPin = FindPin(GetClassExecPinName(MyClass));

		UClass* StaticClassType = Cast<UClass>(OutputObjectClassPin->PinType.PinSubCategoryObject.Get());

		// Creating the cast node
		auto CastNode = BeamK2::CreateDynamicCastNode(this, CompilerContext, SourceGraph, StaticClassType, false);

		// Change the type of the cast node source pin to match the Input Pin
		CastNode->GetCastSourcePin()->PinType = GetInputPin()->PinType;

		// Link the input pin and the cast source pin

		if (K2Schema->TryCreateConnection(InputLinkPin, CastNode->GetCastSourcePin()))
		{
			InputLinkPin->MakeLinkTo(CastNode->GetCastSourcePin());
		}

		// Link the cast result with the output class pin
		const auto CastWork = CompilerContext.MovePinLinksToIntermediate(*OutputObjectClassPin, *CastNode->GetCastResultPin());
		check(!CastWork.IsFatal());

		// Link the cast valid with the output class pin
		const auto SuccessFlowMovedCastSuccess = CompilerContext.MovePinLinksToIntermediate(*OutputExecuteClassPin, *CastNode->GetValidCastPin());
		check(!SuccessFlowMovedCastSuccess.IsFatal());

		if (FirstCast)
		{
			// Link the execute pin and the cast node execute
			const auto CastWork2 = CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CastNode->GetExecPin());
			check(!CastWork2.IsFatal());


			FirstCast = false;
		}
		else
		{
			// Link the execute pin and the cast node execute
			auto CastWork2 = K2Schema->TryCreateConnection(CastNode->GetExecPin(), InvalidCastPin);
			check(CastWork2);
		}

		// Cache the invalid cast pin to the next connection
		InvalidCastPin = CastNode->GetInvalidCastPin();
	}
	// After create all the pins we connect the last fail cast to the then pin for node
	if (InvalidCastPin)
	{
		UClass* StaticClassType = Cast<UClass>(GetDefaultOutputPin()->PinType.PinSubCategoryObject.Get());

		// Creating the cast node
		auto CastNode = BeamK2::CreateDynamicCastNode(this, CompilerContext, SourceGraph, StaticClassType, false);

		// Change the type of the cast node source pin to match the Input Pin
		CastNode->GetCastSourcePin()->PinType = GetInputPin()->PinType;

		// Link the input pin and the cast source pin
		if (K2Schema->TryCreateConnection(InputLinkPin, CastNode->GetCastSourcePin()))
		{
			InputLinkPin->MakeLinkTo(CastNode->GetCastSourcePin());
		}

		// Link the cast result with the output class pin
		const auto Connect2 = CompilerContext.MovePinLinksToIntermediate(*GetDefaultOutputPin(), *CastNode->GetCastResultPin());
		check(!Connect2.IsFatal());

		// Link the cast valid with the output class pin
		const auto SuccessFlowMovedCastSuccess = CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *CastNode->GetValidCastPin());
		check(!SuccessFlowMovedCastSuccess.IsFatal());

		// Link the execute pin and the cast node execute
		if (FirstCast)
		{
			// Link the execute pin and the cast node execute
			const auto CastWork2 = CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CastNode->GetExecPin());
			check(!CastWork2.IsFatal());
		}
		else
		{
			// Link the execute pin and the cast node execute
			auto CastWork2 = K2Schema->TryCreateConnection(InvalidCastPin, CastNode->GetExecPin());
			check(CastWork2);
		}
	}
}

void UK2BeamNode_Switch::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

void UK2BeamNode_Switch::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);

	if (!Context->bIsDebugging)
	{
		FToolMenuSection& Section = Menu->AddSection("UK2BeamNode_Switch", NSLOCTEXT("K2Nodes", "UK2BeamNode_SwitchHeader", "Switch Node"));

		FTextKey LLOCTEXT_NAMESPACE;
		if (Context->Pin != NULL)
		{
			if (Context->Pin->Direction == EGPD_Input && Context->Pin->ParentPin == nullptr)
			{
				Section.AddMenuEntry(
					"RemovePin",
					LOCTEXT("RemovePin", "Remove array element pin"),
					LOCTEXT("RemovePinTooltip", "Remove this array element pin"),
					FSlateIcon(),
					FUIAction(
						FExecuteAction::CreateUObject(const_cast<UK2BeamNode_Switch*>(this), &UK2BeamNode_Switch::RemoveInputPin, const_cast<UEdGraphPin*>(Context->Pin))
					)
				);
			}
		}
		else
		{
			// Section.AddMenuEntry(
			// 	"AddPin",
			// 	LOCTEXT("AddPin", "Add array element pin"),
			// 	LOCTEXT("AddPinTooltip", "Add another array element pin"),
			// 	FSlateIcon(),
			// 	FUIAction(
			// 		FExecuteAction::CreateUObject(const_cast<UK2BeamNode_Switch*>(this), &UK2BeamNode_Switch::InteractiveAddInputPin)
			// 	)
			// );
		}

		// Section.AddMenuEntry(
		// 	"ResetToWildcard",
		// 	LOCTEXT("ResetToWildcard", "Reset to wildcard"),
		// 	LOCTEXT("ResetToWildcardTooltip", "Reset the node to have wildcard input/outputs. Requires no pins are connected."),
		// 	FSlateIcon(),
		// 	FUIAction(
		// 		FExecuteAction::CreateUObject(const_cast<UK2BeamNode_Switch*>(this), &UK2BeamNode_Switch::ClearPinTypeToWildcard),
		// 		FCanExecuteAction::CreateUObject(this, &UK2BeamNode_Switch::CanResetToWildcard)
		// 	)
		// );
	}
}

FSlateIcon UK2BeamNode_Switch::GetIconAndTint(FLinearColor& OutColor) const
{
	Super::GetIconAndTint(OutColor);
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_Switch::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

void UK2BeamNode_Switch::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const auto PropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_Switch, InputsNum);
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetNameCPP().Equals(PropName.ToString()))
	{
		ReconstructNode();
	}
}

void UK2BeamNode_Switch::AddInputPin()
{
	Modify();
	int32 Inputs = 0;
	while (true)
	{
		FName NewName = GetClassInputPinName(Inputs);
		if (!DefaultValue.Contains(NewName))
		{
			DefaultValue.Add(NewName);
			break;
		}
		Inputs++;
	}

	ReconstructNode();
}

void UK2BeamNode_Switch::RemoveInputPin(UEdGraphPin* Pin)
{
	check(Pin->Direction == EGPD_Input);
	check(Pin->ParentPin == nullptr);
	checkSlow(Pins.Contains(Pin));

	FTextKey LLOCTEXT_NAMESPACE;
	FScopedTransaction Transaction(LOCTEXT("RemovePinTx", "RemovePin"));
	Modify();

	TFunction<void(UEdGraphPin*)> RemovePinLambda = [this, &RemovePinLambda](UEdGraphPin* PinToRemove)
	{
		for (int32 SubPinIndex = PinToRemove->SubPins.Num() - 1; SubPinIndex >= 0; --SubPinIndex)
		{
			RemovePinLambda(PinToRemove->SubPins[SubPinIndex]);
		}

		int32 PinRemovalIndex = INDEX_NONE;
		if (Pins.Find(PinToRemove, PinRemovalIndex))
		{
			Pins.RemoveAt(PinRemovalIndex);
			PinToRemove->MarkAsGarbage();
		}
	};

	if (DefaultValue.Contains(Pin->PinName))
	{
		DefaultValue.Remove(Pin->PinName);
	}


	RemovePinLambda(Pin);
	// PinConnectionListChanged(Pin);
	// FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	ReconstructNode();
}

void UK2BeamNode_Switch::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	Super::PinDefaultValueChanged(Pin);
	FString ClassName;
	FString _;
	Pin->GetDefaultAsString().Split(TEXT("."), &_, &ClassName);

	DefaultValue.Add(Pin->PinName, ClassName);
	ReconstructNode();
}

void UK2BeamNode_Switch::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::NotifyPinConnectionListChanged(Pin);

	if (Pin->ParentPin == nullptr)
	{
		UpdateWildcardPinsType();
	}
}

void UK2BeamNode_Switch::PostReconstructNode()
{
	UpdateWildcardPinsType();
	Super::PostReconstructNode();
}

void UK2BeamNode_Switch::UpdateWildcardPinsType() const
{
	UEdGraphPin* InputPin = GetInputPin();
	UEdGraphPin* OutputPin = GetDefaultOutputPin();

	if (!InputPin || !OutputPin)
	{
		return;
	}

	if (InputPin->LinkedTo.Num() > 0 && !InputPin->LinkedTo[0]->PinType.PinSubCategoryObject->IsA(UClass::StaticClass()))
	{
		InputPin->BreakAllPinLinks();
	}

	if (OutputPin->LinkedTo.Num() > 0 && !OutputPin->LinkedTo[0]->PinType.PinSubCategoryObject->IsA(UClass::StaticClass()))
	{
		OutputPin->BreakAllPinLinks();
	}

	if (InputPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard && InputPin->LinkedTo.Num() > 0)
	{
		InputPin->PinType = InputPin->LinkedTo[0]->PinType;
		OutputPin->PinType = InputPin->LinkedTo[0]->PinType;
	}
	if (OutputPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard && OutputPin->LinkedTo.Num() > 0)
	{
		InputPin->PinType = OutputPin->LinkedTo[0]->PinType;
		OutputPin->PinType = OutputPin->LinkedTo[0]->PinType;
	}

	if (InputPin->LinkedTo.Num() == 0 && OutputPin->LinkedTo.Num() == 0)
	{
		InputPin->PinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
		InputPin->PinType.PinSubCategory = TEXT("");
		InputPin->PinType.PinSubCategoryObject = NULL;

		OutputPin->PinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
		OutputPin->PinType.PinSubCategory = TEXT("");
		OutputPin->PinType.PinSubCategoryObject = NULL;

		InputPin->BreakAllPinLinks();
		OutputPin->BreakAllPinLinks();
	}
}

UEdGraphPin* UK2BeamNode_Switch::GetInputPin() const
{
	return FindPin(InputPinName);
}

UEdGraphPin* UK2BeamNode_Switch::GetDefaultOutputPin() const
{
	return FindPin(OutputPinName);
}

FName UK2BeamNode_Switch::GetPinName(int32 PinIndex) const
{
	return *FString::Printf(TEXT("[%d]"), PinIndex);
}

FNodeHandlingFunctor* UK2BeamNode_Switch::CreateNodeHandler(FKismetCompilerContext& CompilerContext) const
{
	return new FNodeHandlingFunctor(CompilerContext);
}
