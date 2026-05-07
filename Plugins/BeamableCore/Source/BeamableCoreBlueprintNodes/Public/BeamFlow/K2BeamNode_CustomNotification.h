// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"

#include "K2BeamNode_CustomNotification.generated.h"

/**
 * Blueprint K2Node — Subscribe to a custom Beamable notification by routing key.
 *
 * Mirrors the C++ ergonomics of UBeamRuntime::SubscribeToCustomNotification<THandler, TMessage> for Blueprint authors.
 * The author picks a USTRUCT (FBeamJsonSerializableUStruct subclass) OR a UClass (IBeamJsonSerializableUObject implementer)
 * via the MessageStruct / MessageClass pins; the node retypes the wildcard "Message" payload output to match.
 *
 * Pins:
 *  - In:  Exec, UserSlot (FUserSlot), Key (FString), MessageStruct (UScriptStruct*) / MessageClass (UClass*) — pick one.
 *  - Out: Then (post-subscribe), OnReceived (multi-shot, fires every notification), Message (typed wildcard payload),
 *         OutHandle (FBeamDelegateHandle — pass to the Unsubscribe node).
 *
 * Expansion: Spawns a CallFunction to the matching dynamic-typed Subscribe entry on UBeamRuntime, plus a UK2Node_Event
 * bound to the dynamic delegate. For the struct path, inserts a CustomThunk call to UBeamNotifications::K2_CopyNotificationStructPayload
 * to copy the alloca'd payload into the typed Message pin. For the object path, inserts a UK2Node_DynamicCast.
 */
UCLASS()
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_SubscribeCustomNotification : public UK2Node
{
	GENERATED_BODY()

public:
	/** The picked USTRUCT message type (mutually exclusive with SelectedMessageClass). */	
	TSoftObjectPtr<UScriptStruct> SelectedMessageStruct;

	/** The picked UObject message class (mutually exclusive with SelectedMessageStruct). */	
	TSoftObjectPtr<UClass> SelectedMessageClass;

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	virtual void PostLoad() override;

private:
	/** Resolves SelectedMessageStruct / SelectedMessageClass into the live picked type, exclusive. */
	UScriptStruct* GetSelectedStruct() const;
	UClass* GetSelectedClass() const;
};

/**
 * Blueprint K2Node — Unsubscribe a previously-Subscribed custom notification handler.
 *
 * Symmetric to UK2BeamNode_SubscribeCustomNotification. Takes the FBeamDelegateHandle returned by the Subscribe node
 * (plus the same Slot + Key) and removes the handler from the underlying UBeamNotifications message-handler table.
 *
 * Modeled after UK2BeamNode_EventUnregister so the discoverability and visual style match the existing event-binding nodes.
 */
UCLASS()
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_UnsubscribeCustomNotification : public UK2Node
{
	GENERATED_BODY()

public:
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
};
