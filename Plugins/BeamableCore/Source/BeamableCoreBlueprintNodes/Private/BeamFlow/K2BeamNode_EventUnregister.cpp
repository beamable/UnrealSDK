// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_EventUnregister.h"

#include "BeamK2.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_AssignDelegate.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"
#include "SourceCodeNavigation.h"

void UK2BeamNode_EventUnregister::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}


void UK2BeamNode_EventUnregister::AllocateDefaultPins()
{
	UK2Node::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	// Create the input execution flow pin
	const auto ExecPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	ExecPin->PinFriendlyName = FText::FromName(UEdGraphSchema_K2::PC_Exec);

	// Create the out execution flow pin
	const auto ThenPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	ThenPin->PinFriendlyName = FText::FromName(UEdGraphSchema_K2::PN_Then);

	const auto ReferenceClass = GetRuntimeSubsystemClass();

	// Iterate over all FMulticastDelegateProperty (bluprintassingnable delegates) and create the pin
	for (TFieldIterator<FMulticastDelegateProperty> It(ReferenceClass); It; ++It)
	{
		FMulticastDelegateProperty* DelegateProp = *It;
		if (DelegateProp && IsValidProperty(DelegateProp))
		{
			BeamK2::CreateEventPinFromProperty(this, DelegateProp);
		}
	}
}


FSlateIcon UK2BeamNode_EventUnregister::GetIconAndTint(FLinearColor& OutColor) const
{
	UK2Node::GetIconAndTint(OutColor);
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_EventUnregister::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

void UK2BeamNode_EventUnregister::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UK2Node::PostEditChangeProperty(PropertyChangedEvent);

	const auto FlowPropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_EventUnregister, EventPins);
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetNameCPP().Equals(FlowPropName.ToString()))
	{
		ReconstructNode();
	}
}

void UK2BeamNode_EventUnregister::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Create the GetSelfCallFunction to get subsystem reference into the delegate target
	auto CallGetSubsystem = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetSubsystemSelfFunctionName(), GetRuntimeSubsystemClass());

	const auto ReferenceClass = GetRuntimeSubsystemClass();

	// The OutputPin will be used to create a chain of RemoveDelegateNode, so it will get the then pin from each RemoveDelegateNode and connect to the next ExecPin
	// After do for every FMulticastDelegateProperty it will connect the remaining reference to the MainNode ThenPin.
	UEdGraphPin* OutputPin = nullptr;

	// Iterate over all the FMulticastDelegateProperty to unbind then.
	for (TFieldIterator<FMulticastDelegateProperty> It(ReferenceClass); It; ++It)
	{
		FMulticastDelegateProperty* DelegateProp = *It;

		if (DelegateProp && IsValidProperty(DelegateProp))
		{
			auto DelegatePropPin = FindPin(DelegateProp->GetFName());

			// If the pin is not connect we will just ignore it to prevent the error for non connected events
			// Event Dispatcher pin is not connected 
			if (DelegatePropPin->LinkedTo.Num() == 0)
			{
				continue;
			}

			// Create the RemoveDelegate node which will be responsible for unbind the delegate
			auto RemoveDelegateNode = BeamK2::CreateRemoveDelegateNode(this, CompilerContext, SourceGraph, DelegateProp);

			auto RemoveDelegate_Self = K2Schema->FindSelfPin(*RemoveDelegateNode, EGPD_Input);
			auto RemoveDelegate_Delegate = RemoveDelegateNode->FindPin(TEXT("Delegate"));

			auto RemoveDelegate_ExecPin = RemoveDelegateNode->GetExecPin();
			auto RemoveDelegate_ThenPin = RemoveDelegateNode->GetThenPin();


			// Connect the node with the target subsystem
			const auto SubsystemReturnPin = CallGetSubsystem->GetReturnValuePin();
			const auto _ = K2Schema->TryCreateConnection(SubsystemReturnPin, RemoveDelegate_Self);

			// Connect the DelegateProperty Pin to the RemoveDelegateNode Delegate Pin
			CompilerContext.MovePinLinksToIntermediate(*DelegatePropPin, *RemoveDelegate_Delegate);


			if (OutputPin == nullptr)
			{
				CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *RemoveDelegate_ExecPin);
			}
			else
			{
				K2Schema->TryCreateConnection(OutputPin, RemoveDelegate_ExecPin);
			}


			OutputPin = RemoveDelegate_ThenPin;
		}
	}


	if (OutputPin != nullptr)
	{
		CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *OutputPin);
	}
	else // This is the case of there's no event unbinded or there's no event at all in the target class.
	{
		CompilerContext.MessageLog.Error(TEXT("[EventRegister Node] There's no event unbiding for (@@) (@@)"), *GetRuntimeSubsystemClass()->GetName(), this);
	}

	// Break original links
	BreakAllNodeLinks();
}

UObject* UK2BeamNode_EventUnregister::GetJumpTargetForDoubleClick() const
{
	const auto ClassReference = GetRuntimeSubsystemClass();

	if (!ClassReference) return nullptr;

	FSourceCodeNavigation::NavigateToClass(ClassReference);

	return UK2Node::GetJumpTargetForDoubleClick();
}

FName UK2BeamNode_EventUnregister::GetSubsystemSelfFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

UClass* UK2BeamNode_EventUnregister::GetRuntimeSubsystemClass() const
{
	return UClass::StaticClass();
}


bool UK2BeamNode_EventUnregister::IsValidProperty(FMulticastDelegateProperty* DelegateProp)
{
	if (!DelegateProp->HasAnyPropertyFlags(CPF_BlueprintAssignable))
	{
		return false;
	}
	FName Name = DelegateProp->GetFName();
	if (!EventPins.Contains(Name))
	{
		EventPins.Add(Name, true);
	}
	return EventPins[Name];
}
