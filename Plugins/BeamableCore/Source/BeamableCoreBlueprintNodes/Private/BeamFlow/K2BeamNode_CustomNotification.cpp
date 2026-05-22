// Fill out your copyright notice in the Description page of Project Settings.

#include "BeamFlow/K2BeamNode_CustomNotification.h"

#include "BeamK2.h"
#include "BeamLogging.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_CallFunction.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_Event.h"
#include "KismetCompiler.h"

#include "BeamNotifications/BeamNotifications.h"
#include "Runtime/BeamRuntime.h"
#include "Serialization/BeamJsonSerializable.h"
#include "UserSlots/UserSlot.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_CustomNotification"

namespace
{
	const FName PN_UserSlot      = TEXT("UserSlot");
	const FName PN_Key           = TEXT("Key");
	const FName PN_MessageStruct = TEXT("MessageStruct");
	const FName PN_MessageClass  = TEXT("MessageClass");
	const FName PN_OnReceived    = TEXT("OnReceived");
	const FName PN_Message       = TEXT("Message");
	const FName PN_OutHandle     = TEXT("OutHandle");
	const FName PN_Handle        = TEXT("Handle");
	const FName PN_Success       = TEXT("bSuccess");
}

// =====================================================================================================================
// UK2BeamNode_SubscribeCustomNotification
// =====================================================================================================================

void UK2BeamNode_SubscribeCustomNotification::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);
		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2BeamNode_SubscribeCustomNotification::GetMenuCategory() const
{
	return FText::FromString(TEXT("Beam|Notifications"));
}

FText UK2BeamNode_SubscribeCustomNotification::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("Title", "Subscribe to Custom Notification");
}

FText UK2BeamNode_SubscribeCustomNotification::GetTooltipText() const
{
	return LOCTEXT("Tooltip",
		"Subscribes to a Beamable custom notification routed by Context Key. Pick either MessageStruct (for USTRUCTs deriving from "
		"FBeamJsonSerializableUStruct) or MessageClass (for UObject classes implementing IBeamJsonSerializableUObject); the Message "
		"output is retyped to match. OnReceived fires every time the notification arrives. Save OutHandle and pass it to the "
		"Unsubscribe Custom Notification node when you're done.");
}

FSlateIcon UK2BeamNode_SubscribeCustomNotification::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_SubscribeCustomNotification::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

UScriptStruct* UK2BeamNode_SubscribeCustomNotification::GetSelectedStruct() const
{
	return SelectedMessageStruct.LoadSynchronous();
}

UClass* UK2BeamNode_SubscribeCustomNotification::GetSelectedClass() const
{
	return SelectedMessageClass.LoadSynchronous();
}

void UK2BeamNode_SubscribeCustomNotification::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Exec in / Then.
	CreatePin(EGPD_Input,  UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	// UserSlot input.
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FUserSlot::StaticStruct(), PN_UserSlot);

	// Key input.
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, PN_Key);

	// MessageStruct picker — only enabled when MessageClass is unset.
	UEdGraphPin* StructPickerPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UScriptStruct::StaticClass(), PN_MessageStruct);
	if (UScriptStruct* PickedStruct = GetSelectedStruct())
	{
		StructPickerPin->DefaultObject = PickedStruct;
	}

	// MessageClass picker — only enabled when MessageStruct is unset.
	UEdGraphPin* ClassPickerPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Class, UObject::StaticClass(), PN_MessageClass);
	if (UClass* PickedClass = GetSelectedClass())
	{
		ClassPickerPin->DefaultObject = PickedClass;
	}

	// OnReceived multi-shot exec.
	UEdGraphPin* OnReceivedPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, PN_OnReceived);
	OnReceivedPin->PinFriendlyName = LOCTEXT("OnReceived", "On Received");

	// Wildcard / typed Message payload output.
	UEdGraphPin* MessagePin = nullptr;
	if (UScriptStruct* PickedStruct = GetSelectedStruct())
	{
		MessagePin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, PickedStruct, PN_Message);
	}
	else if (UClass* PickedClass = GetSelectedClass())
	{
		MessagePin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, PickedClass, PN_Message);
	}
	else
	{
		MessagePin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, PN_Message);
	}
	MessagePin->PinFriendlyName = LOCTEXT("Message", "Message");

	// OutHandle (FBeamDelegateHandle).
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FBeamDelegateHandle::StaticStruct(), PN_OutHandle);
}

void UK2BeamNode_SubscribeCustomNotification::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	Super::PinDefaultValueChanged(Pin);

	bool bShouldReconstruct = false;
	if (Pin->PinName == PN_MessageStruct)
	{
		UScriptStruct* NewStruct = Cast<UScriptStruct>(Pin->DefaultObject.Get());
		if (NewStruct != GetSelectedStruct())
		{
			SelectedMessageStruct = NewStruct;
			if (NewStruct)
			{
				// Picking a struct clears any previously-picked class — modes are mutually exclusive.
				SelectedMessageClass.Reset();
				if (UEdGraphPin* ClassPin = FindPin(PN_MessageClass))
				{
					ClassPin->DefaultObject = nullptr;
					ClassPin->ResetDefaultValue();
				}
			}
			bShouldReconstruct = true;
		}
	}
	else if (Pin->PinName == PN_MessageClass)
	{
		UClass* NewClass = Cast<UClass>(Pin->DefaultObject.Get());
		if (NewClass != GetSelectedClass())
		{
			SelectedMessageClass = NewClass;
			if (NewClass)
			{
				SelectedMessageStruct.Reset();
				if (UEdGraphPin* StructPin = FindPin(PN_MessageStruct))
				{
					StructPin->DefaultObject = nullptr;
					StructPin->ResetDefaultValue();
				}
			}
			bShouldReconstruct = true;
		}
	}

	if (bShouldReconstruct)
	{
		ReconstructNode();
	}
}

void UK2BeamNode_SubscribeCustomNotification::PostLoad()
{
	Super::PostLoad();
	// Force-resolve the soft pointers and reconstruct so renames / hot-reload land cleanly.
	SelectedMessageStruct.LoadSynchronous();
	SelectedMessageClass.LoadSynchronous();
}

void UK2BeamNode_SubscribeCustomNotification::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	UScriptStruct* PickedStruct = GetSelectedStruct();
	UClass*        PickedClass  = GetSelectedClass();

	if (!PickedStruct && !PickedClass)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("NoMessageType", "Subscribe to Custom Notification: pick either a MessageStruct or a MessageClass before compiling.").ToString(), this);
		BreakAllNodeLinks();
		return;
	}
	if (PickedStruct && PickedClass)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("BothPicked", "Subscribe to Custom Notification: only one of MessageStruct or MessageClass may be set.").ToString(), this);
		BreakAllNodeLinks();
		return;
	}
	if (PickedStruct && !PickedStruct->IsChildOf(FBeamJsonSerializableUStruct::StaticStruct()))
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("BadStruct", "Subscribe to Custom Notification: MessageStruct must derive from FBeamJsonSerializableUStruct.").ToString(), this);
		BreakAllNodeLinks();
		return;
	}
	if (PickedClass && !PickedClass->ImplementsInterface(UBeamJsonSerializableUObject::StaticClass()))
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("BadClass", "Subscribe to Custom Notification: MessageClass must implement IBeamJsonSerializableUObject.").ToString(), this);
		BreakAllNodeLinks();
		return;
	}

	// 1. GetSelf<UBeamRuntime>.
	UK2Node_CallFunction* CallGetSelf = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph,
		GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf), UBeamRuntime::StaticClass());

	// 2. CallSubscribe — picks the struct or object dynamic-typed entry point.
	const FName SubscribeFnName = PickedStruct
		? GET_FUNCTION_NAME_CHECKED(UBeamRuntime, SubscribeToCustomNotification_DynamicStruct)
		: GET_FUNCTION_NAME_CHECKED(UBeamRuntime, SubscribeToCustomNotification_DynamicObject);
	UK2Node_CallFunction* CallSubscribe = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph,
		SubscribeFnName, UBeamRuntime::StaticClass());

	BeamK2::SetUpPinsFunctionToOwnerSubsystem(CallGetSelf, CallSubscribe);

	// 3. Wire main exec flow.
	CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CallSubscribe->GetExecPin());
	CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *CallSubscribe->GetThenPin());

	// 4. Wire user-facing inputs: UserSlot, Key.
	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_UserSlot), *CallSubscribe->FindPinChecked(TEXT("UserSlot")));
	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_Key),      *CallSubscribe->FindPinChecked(TEXT("Key")));

	// 5. Bake the picked type as the literal default on the call's MessageType / MessageClass input.
	if (PickedStruct)
	{
		UEdGraphPin* TypePin = CallSubscribe->FindPinChecked(TEXT("MessageType"));
		TypePin->DefaultObject = PickedStruct;
	}
	else
	{
		UEdGraphPin* ClassPin = CallSubscribe->FindPinChecked(TEXT("MessageClass"));
		ClassPin->DefaultObject = PickedClass;
	}

	// 6. ContextObject — leave the call's pin defaulted; the runtime falls back to the runtime instance itself.
	//    (DefaultToSelf-style wiring would need a Self ref pin on this K2Node, which we don't expose to keep the
	//    pinout minimal. ContextObject's only role is PIE namespacing, which the runtime itself satisfies.)

	// 7. OutHandle.
	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_OutHandle), *CallSubscribe->GetReturnValuePin());

	// 8. CustomEvent (UK2Node_Event signature-bound to the dynamic delegate type).
	const TCHAR* DelegateTypeName = PickedStruct
		? TEXT("OnBeamCustomNotificationStructDynamic")
		: TEXT("OnBeamCustomNotificationObjectDynamic");
	UK2Node_Event* EventNode = BeamK2::CreateEventNodeForDelegate(this, CompilerContext, SourceGraph, FString(DelegateTypeName));

	// 9. Wire EventNode's outgoing delegate → CallSubscribe's "Handler" parameter.
	UEdGraphPin* HandlerInputPin = CallSubscribe->FindPinChecked(TEXT("Handler"), EGPD_Input);
	UEdGraphPin* EventDelegatePin = EventNode->FindPinChecked(EventNode->DelegateOutputName);
	K2Schema->TryCreateConnection(EventDelegatePin, HandlerInputPin);

	// 10. Branch on mode for payload-decoding wiring.
	UEdGraphPin* OurOnReceivedPin = FindPinChecked(PN_OnReceived);
	UEdGraphPin* OurMessagePin    = FindPinChecked(PN_Message);

	if (PickedStruct)
	{
		// Insert the CustomThunk call that copies the alloca'd payload into the typed Message pin.
		UK2Node_CallFunction* CallCopy = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph,
			GET_FUNCTION_NAME_CHECKED(UBeamNotifications, K2_CopyNotificationStructPayload), UBeamNotifications::StaticClass());

		// Wire EventNode's "Payload" param → CallCopy's Payload input.
		UEdGraphPin* EventPayloadPin = EventNode->FindPinChecked(TEXT("Payload"));
		UEdGraphPin* CopyPayloadPin  = CallCopy->FindPinChecked(TEXT("Payload"), EGPD_Input);
		K2Schema->TryCreateConnection(EventPayloadPin, CopyPayloadPin);

		// Retype the CustomThunk's wildcard "OutMessage" pin to the picked struct so user wires connect cleanly.
		UEdGraphPin* CopyOutMessagePin = CallCopy->FindPinChecked(TEXT("OutMessage"));
		CopyOutMessagePin->PinType.PinCategory = UEdGraphSchema_K2::PC_Struct;
		CopyOutMessagePin->PinType.PinSubCategoryObject = PickedStruct;

		// Exec wiring: EventNode.Then → CallCopy.Exec → user OnReceived.
		K2Schema->TryCreateConnection(EventNode->FindPinChecked(UEdGraphSchema_K2::PN_Then), CallCopy->GetExecPin());
		CompilerContext.MovePinLinksToIntermediate(*OurOnReceivedPin, *CallCopy->GetThenPin());

		// Move user's typed Message pin links to the CustomThunk's OutMessage.
		CompilerContext.MovePinLinksToIntermediate(*OurMessagePin, *CopyOutMessagePin);
	}
	else
	{
		// Object mode: EventNode's "Object" output is a UObject*. Insert a DynamicCast to the picked UClass.
		UK2Node_DynamicCast* CastNode = BeamK2::CreateDynamicCastNode(this, CompilerContext, SourceGraph, PickedClass, false /* not pure */);

		UEdGraphPin* EventObjectPin = EventNode->FindPinChecked(TEXT("Object"));
		K2Schema->TryCreateConnection(EventObjectPin, CastNode->GetCastSourcePin());

		// Exec wiring: EventNode.Then → Cast.Exec; cast valid → user OnReceived.
		K2Schema->TryCreateConnection(EventNode->FindPinChecked(UEdGraphSchema_K2::PN_Then), CastNode->GetExecPin());
		CompilerContext.MovePinLinksToIntermediate(*OurOnReceivedPin, *CastNode->GetValidCastPin());

		// Move user's typed Message pin links to the cast result.
		CompilerContext.MovePinLinksToIntermediate(*OurMessagePin, *CastNode->GetCastResultPin());
	}

	BreakAllNodeLinks();
}

// =====================================================================================================================
// UK2BeamNode_UnsubscribeCustomNotification
// =====================================================================================================================

void UK2BeamNode_UnsubscribeCustomNotification::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);
		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2BeamNode_UnsubscribeCustomNotification::GetMenuCategory() const
{
	return FText::FromString(TEXT("Beam|Notifications"));
}

FText UK2BeamNode_UnsubscribeCustomNotification::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("UnsubscribeTitle", "Unsubscribe Custom Notification");
}

FText UK2BeamNode_UnsubscribeCustomNotification::GetTooltipText() const
{
	return LOCTEXT("UnsubscribeTooltip",
		"Unsubscribes a previously-registered custom notification handler. Pass the FBeamDelegateHandle that the "
		"Subscribe to Custom Notification node returned, plus the same UserSlot and Key.");
}

FSlateIcon UK2BeamNode_UnsubscribeCustomNotification::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = FLinearColor::FromSRGBColor(FColor::FromHex("#826CCF"));
	return FSlateIcon(TEXT("BeamableCore"), "BeamIconSmall");
}

FLinearColor UK2BeamNode_UnsubscribeCustomNotification::GetNodeTitleColor() const
{
	return FLinearColor::FromSRGBColor(FColor::FromHex("#674CC5"));
}

void UK2BeamNode_UnsubscribeCustomNotification::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	CreatePin(EGPD_Input,  UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FUserSlot::StaticStruct(),         PN_UserSlot);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String,                                    PN_Key);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FBeamDelegateHandle::StaticStruct(), PN_Handle);

	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Boolean, PN_Success);
}

void UK2BeamNode_UnsubscribeCustomNotification::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UK2Node::ExpandNode(CompilerContext, SourceGraph);

	UK2Node_CallFunction* CallGetSelf = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph,
		GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf), UBeamRuntime::StaticClass());
	UK2Node_CallFunction* CallUnsubscribe = BeamK2::CreateCallFunctionNode(this, CompilerContext, SourceGraph,
		GET_FUNCTION_NAME_CHECKED(UBeamRuntime, UnsubscribeToCustomNotification_BP), UBeamRuntime::StaticClass());

	BeamK2::SetUpPinsFunctionToOwnerSubsystem(CallGetSelf, CallUnsubscribe);

	CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *CallUnsubscribe->GetExecPin());
	CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *CallUnsubscribe->GetThenPin());

	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_UserSlot), *CallUnsubscribe->FindPinChecked(TEXT("UserSlot")));
	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_Key),      *CallUnsubscribe->FindPinChecked(TEXT("Key")));
	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_Handle),   *CallUnsubscribe->FindPinChecked(TEXT("Handle")));

	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(PN_Success),  *CallUnsubscribe->GetReturnValuePin());

	BreakAllNodeLinks();
}

#undef LOCTEXT_NAMESPACE
