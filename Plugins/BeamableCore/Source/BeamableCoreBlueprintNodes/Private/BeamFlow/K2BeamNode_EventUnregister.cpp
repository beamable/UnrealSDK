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

	UClass* ReferenceClass = GetRuntimeSubsystemClass();
	if (ShouldUsesObject())
	{
		const auto ObjectPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), UEdGraphSchema_K2::PN_ObjectToCast);

		auto ObjectClass = GetClassFromObject();
		if (ObjectClass)
		{
			ReferenceClass = ObjectClass;
		}
	}

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

	const auto ObjectPropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_EventUnregister, ShouldUsesObject());
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetNameCPP().Equals(ObjectPropName.ToString()))
	{
		ReconstructNode();
	}
}

void UK2BeamNode_EventUnregister::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	
	UK2Node_CallFunction* CallGetSubsystem = nullptr;
	
	UClass* ReferenceClass = GetRuntimeSubsystemClass();

	if (ShouldUsesObject())
	{
		auto ObjectLinks = FindPin(UEdGraphSchema_K2::PN_ObjectToCast)->LinkedTo;
		if (ObjectLinks.Num() > 0)
		{
			ReferenceClass = ObjectLinks[0]->PinType.PinSubCategoryObject->GetClass();
		}
	}else
	{
		// Create the GetSelfCallFunction to get subsystem reference into the delegate target
		CallGetSubsystem = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetSubsystemSelfFunctionName(), GetRuntimeSubsystemClass());
	}

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


			if (ShouldUsesObject())
			{
				auto ObjectPin = FindPin(UEdGraphSchema_K2::PN_ObjectToCast);
				if (ObjectPin->LinkedTo.Num() > 0 && K2Schema->TryCreateConnection(ObjectPin->LinkedTo[0], RemoveDelegate_Self))
				{
					ObjectPin->LinkedTo[0]->MakeLinkTo(RemoveDelegate_Self);
				}
			}
			else
			{
				// Connect the node with the target subsystem
				const auto SubsystemReturnPin = CallGetSubsystem->GetReturnValuePin();
				const auto _ = K2Schema->TryCreateConnection(SubsystemReturnPin, RemoveDelegate_Self);
			}

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

void UK2BeamNode_EventUnregister::JumpToDefinition() const
{
	const auto ClassReference = GetRuntimeSubsystemClass();

	if (!ClassReference) return;

	FSourceCodeNavigation::NavigateToClass(ClassReference);
}

FName UK2BeamNode_EventUnregister::GetSubsystemSelfFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

void UK2BeamNode_EventUnregister::NodeConnectionListChanged()
{
	Super::NodeConnectionListChanged();

	if (ShouldUsesObject())
	{
		auto Pin = FindPin(UEdGraphSchema_K2::PN_ObjectToCast);
		if (Pin->LinkedTo.Num() > 0)
		{
			UClass* StaticClassType = Cast<UClass>(Pin->LinkedTo[0]->PinType.PinSubCategoryObject.Get());
			ClassStr = FSoftClassPath{StaticClassType}.GetAssetPath().ToString();
		}
	}

	ReconstructNode();
}

UClass* UK2BeamNode_EventUnregister::GetRuntimeSubsystemClass() const
{
	return GetClassFromObject();
}

UClass* UK2BeamNode_EventUnregister::GetClassFromObject() const
{
	if (!ClassStr.IsEmpty())
	{
		return FSoftClassPath{ClassStr}.ResolveClass();
	}
	return UObject::StaticClass();
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
