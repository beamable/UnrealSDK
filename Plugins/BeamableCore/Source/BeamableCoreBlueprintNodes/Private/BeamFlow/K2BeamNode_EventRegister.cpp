// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamFlow/K2BeamNode_EventRegister.h"

#include "BeamK2.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_AssignDelegate.h"
#include "K2Node_CallFunction.h"
#include "K2Node_CustomEvent.h"
#include "KismetCompiler.h"
#include "SourceCodeNavigation.h"

void UK2BeamNode_EventRegister::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}


void UK2BeamNode_EventRegister::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	// Create the input execution flow pin
	const auto ExecPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	ExecPin->PinFriendlyName = FText::FromName(UEdGraphSchema_K2::PC_Exec);

	// Create the out execution flow pin
	const auto ThenPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	ThenPin->PinFriendlyName = FText::FromName(FName("After Bind - Then"));

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
			if (ShowAsExecuteProperty(DelegateProp))
			{
				BeamK2::CreateExecutePinFromEventProperty(this, DelegateProp);
			}
			else
			{
				BeamK2::CreateEventPinFromProperty(this, DelegateProp);
			}
		}
	}

	// Iterate over all FMulticastDelegateProperty (bluprintassingnable delegates) and create the pin
	for (TFieldIterator<FMulticastDelegateProperty> It(ReferenceClass); It; ++It)
	{
		FMulticastDelegateProperty* DelegateProp = *It;
		if (DelegateProp && IsValidProperty(DelegateProp) && ShowUnbindAsExecuteProperty(DelegateProp))
		{
			// Create the out execution flow pin
			const auto UnbindPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, FName(DelegateProp->GetName() + TEXT("_Unbind")));
			UnbindPin->PinFriendlyName = FText::FromName(FName(TEXT("Unbind - ") + DelegateProp->GetName()));
		}
	}
}


FSlateIcon UK2BeamNode_EventRegister::GetIconAndTint(FLinearColor& OutColor) const
{
	Super::GetIconAndTint(OutColor);
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_EventRegister::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

void UK2BeamNode_EventRegister::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const auto FlowPropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_EventRegister, EventPins);
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetNameCPP().Equals(FlowPropName.ToString()))
	{
		ReconstructNode();
	}

	const auto ShowEventPropName = GET_MEMBER_NAME_CHECKED(UK2BeamNode_EventRegister, EventPinsAsExecute);
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetNameCPP().Equals(ShowEventPropName.ToString()))
	{
		ReconstructNode();
	}
}


void UK2BeamNode_EventRegister::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Create the GetSelfCallFunction to get subsystem reference into the delegate target
	UK2Node_CallFunction* CallGetSubsystem = nullptr;

	UClass* ReferenceClass = GetRuntimeSubsystemClass();

	if (ShouldUsesObject())
	{
		auto ObjectClass = GetClassFromObject();
		if (ObjectClass)
		{
			ReferenceClass = ObjectClass;
		}
	}
	else
	{
		CallGetSubsystem = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph, GetSubsystemSelfFunctionName(), GetRuntimeSubsystemClass());
	}

	// The OutputPin will be used to create a chain of AddDelegateNode, so it will get the then pin from each AddDelegateNode and connect to the next ExecPin
	// After do for every FMulticastDelegateProperty it will connect the remaining reference to the MainNode ThenPin.
	UEdGraphPin* OutputPin = nullptr;

	TMap<FString, UEdGraphPin*> DelegatePinsMap;

	// Iterate over all the FMulticastDelegateProperty to create bind then.
	for (TFieldIterator<FMulticastDelegateProperty> It(ReferenceClass); It; ++It)
	{
		FMulticastDelegateProperty* DelegateProp = *It;

		if (DelegateProp && IsValidProperty(DelegateProp))
		{
			auto DelegatePropPin = FindPin(DelegateProp->GetFName());

			if (!ShowAsExecuteProperty(DelegateProp) && DelegatePropPin->LinkedTo.Num() == 0)
			{
				continue;
			}

			// Create the AddDelegate node which will be responsible for bind the delegate
			auto AddDelegateNode = BeamK2::CreateAddDelegateNode(this, CompilerContext, SourceGraph, DelegateProp);

			auto AddDelegate_Self = K2Schema->FindSelfPin(*AddDelegateNode, EGPD_Input);
			auto AddDelegate_Delegate = AddDelegateNode->FindPin(TEXT("Delegate"));

			auto AddDelegate_ExecPin = AddDelegateNode->GetExecPin();
			auto AddDelegate_ThenPin = AddDelegateNode->GetThenPin();

			if (ShouldUsesObject())
			{
				auto ObjectPin = FindPin(UEdGraphSchema_K2::PN_ObjectToCast);
				if (ObjectPin->LinkedTo.Num() > 0 && K2Schema->TryCreateConnection(ObjectPin->LinkedTo[0], AddDelegate_Self))
				{
					ObjectPin->LinkedTo[0]->MakeLinkTo(AddDelegate_Self);
				}
			}
			else
			{
				// Connect the node with the target subsystem                                         
				const auto SubsystemReturnPin = CallGetSubsystem->GetReturnValuePin();
				const auto _ = K2Schema->TryCreateConnection(SubsystemReturnPin, AddDelegate_Self);
			}

			if (ShowAsExecuteProperty(DelegateProp))
			{
				auto CustomEventNode = CompilerContext.SpawnIntermediateNode<UK2Node_CustomEvent>(this, SourceGraph);
				auto MemberReference = FMemberReference();
				MemberReference.SetExternalMember(DelegateProp->GetFName(), ReferenceClass);

				CustomEventNode->EventReference = MemberReference;
				CustomEventNode->CustomFunctionName = CompilerContext.GetEventStubFunctionName(CustomEventNode);
				CustomEventNode->SetDelegateSignature(DelegateProp->SignatureFunction);

				CustomEventNode->AllocateDefaultPins();

				CompilerContext.MovePinLinksToIntermediate(*DelegatePropPin, *CustomEventNode->GetThenPin());

				// Connect the Custom Event Delegate Pin to the AddNodeDelegate Delegate Pin
				K2Schema->TryCreateConnection(CustomEventNode->GetDelegatePin(), AddDelegate_Delegate);
				DelegatePinsMap.Add(DelegateProp->GetName(), CustomEventNode->GetDelegatePin());
				//This gives you the function signature that any delegate bound to this must match

				if (UFunction* SignatureFunction = DelegateProp->SignatureFunction)
				{
					for (TFieldIterator<FProperty> Property(SignatureFunction); Property && (Property->PropertyFlags & CPF_Parm); ++Property)
					{
						FProperty* ParamProperty = *Property;

						FString ParamName = DelegateProp->GetName() + TEXT(" - ") + ParamProperty->GetName();

						auto CustomEventPin = CustomEventNode->FindPin(ParamProperty->GetName());

						CompilerContext.MovePinLinksToIntermediate(*FindPin(ParamName), *CustomEventPin);
					}
				}
			}
			else
			{
				// If it's a event, then we get the cached the linked reference to the even
				DelegatePinsMap.Add(DelegateProp->GetName(), DelegatePropPin->LinkedTo[0]);

				// Connect the DelegateProperty Pin to the AddNodeDelegate Delegate Pin
				CompilerContext.MovePinLinksToIntermediate(*DelegatePropPin, *AddDelegate_Delegate);
			}


			if (OutputPin == nullptr)
			{
				CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *AddDelegate_ExecPin);
			}
			else
			{
				K2Schema->TryCreateConnection(OutputPin, AddDelegate_ExecPin);
			}


			OutputPin = AddDelegate_ThenPin;
		}
	}


	if (OutputPin != nullptr)
	{
		CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *OutputPin);
	}
	else // This is the case of there's no event binded or there's no event at all in the target class.
	{
		CompilerContext.MessageLog.Error(TEXT("[EventRegister Node] There's no event binded for (@@) (@@)"), *GetRuntimeSubsystemClass()->GetName(), this);
	}

	// Iterate over all the FMulticastDelegateProperty to create unbind input.
	for (TFieldIterator<FMulticastDelegateProperty> It(ReferenceClass); It; ++It)
	{
		FMulticastDelegateProperty* DelegateProp = *It;

		if (DelegateProp && IsValidProperty(DelegateProp) && ShowUnbindAsExecuteProperty(DelegateProp))
		{
			if (!DelegatePinsMap.Contains(DelegateProp->GetName()))
			{
				continue;
			}

			// Create the RemoveDelegate node which will be responsible for unbind the delegate
			auto RemoveDelegateNode = BeamK2::CreateRemoveDelegateNode(this, CompilerContext, SourceGraph, DelegateProp);

			auto RemoveDelegate_Self = K2Schema->FindSelfPin(*RemoveDelegateNode, EGPD_Input);
			auto RemoveDelegate_Delegate = RemoveDelegateNode->FindPin(TEXT("Delegate"));

			auto RemoveDelegate_ExecPin = RemoveDelegateNode->GetExecPin();

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

			// Create the connection between the cached delegate property and the remove delegate node pin
			K2Schema->TryCreateConnection(DelegatePinsMap[DelegateProp->GetName()], RemoveDelegate_Delegate);

			CompilerContext.MovePinLinksToIntermediate(*FindPin(DelegateProp->GetName() + TEXT("_Unbind")), *RemoveDelegate_ExecPin);
		}
	}

	// Break original links
	BreakAllNodeLinks();
}

void UK2BeamNode_EventRegister::JumpToDefinition() const
{
	const auto ClassReference = GetRuntimeSubsystemClass();

	if (!ClassReference) return;

	FSourceCodeNavigation::NavigateToClass(ClassReference);
}

FName UK2BeamNode_EventRegister::GetSubsystemSelfFunctionName() const
{
	return FName("K2BeamNode_GetState");
}

void UK2BeamNode_EventRegister::NodeConnectionListChanged()
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

UClass* UK2BeamNode_EventRegister::GetRuntimeSubsystemClass() const
{
	return GetClassFromObject();
}


bool UK2BeamNode_EventRegister::IsValidProperty(FMulticastDelegateProperty* DelegateProp)
{
	// It's not valid if is not assignable by blueprint
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

bool UK2BeamNode_EventRegister::ShowAsExecuteProperty(FMulticastDelegateProperty* DelegateProp)
{
	if (!DelegateProp->HasAnyPropertyFlags(CPF_BlueprintAssignable))
	{
		return false;
	}
	FName Name = DelegateProp->GetFName();
	if (!EventPinsAsExecute.Contains(Name))
	{
		EventPinsAsExecute.Add(Name, true);
	}
	return EventPinsAsExecute[Name];
}

bool UK2BeamNode_EventRegister::ShowUnbindAsExecuteProperty(FMulticastDelegateProperty* DelegateProp)
{
	if (!DelegateProp->HasAnyPropertyFlags(CPF_BlueprintAssignable))
	{
		return false;
	}
	FName Name = DelegateProp->GetFName();
	if (!EventUnbindPinsAsExecute.Contains(Name))
	{
		EventUnbindPinsAsExecute.Add(Name, false);
	}
	return EventUnbindPinsAsExecute[Name];
}

UClass* UK2BeamNode_EventRegister::GetClassFromObject() const
{
	if (!ClassStr.IsEmpty())
	{
		return FSoftClassPath{ClassStr}.ResolveClass();
	}
	return UObject::StaticClass();
}
