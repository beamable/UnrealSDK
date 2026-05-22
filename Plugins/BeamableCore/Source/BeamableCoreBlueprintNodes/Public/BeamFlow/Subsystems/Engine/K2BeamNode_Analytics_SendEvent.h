#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"

#include "K2BeamNode_Analytics_SendEvent.generated.h"

class FBlueprintActionDatabaseRegistrar;
class UEdGraph;
class UEdGraphPin;
class FKismetCompilerContext;

/**
 * Custom Blueprint node that lets the user select an FBeamAnalyticsEvent subtype from a
 * dropdown and exposes the struct's fields as input pins. On compile, the node expands
 * into a MakeStruct + a CustomThunk-wrapped subsystem call that enqueues the event.
 *
 * - Dropdown source: every UScriptStruct that derives from FBeamAnalyticsEvent.
 * - Pin layout (after a type is chosen):
 *     Exec In, Then Out, Result(bool) Out, ContextObject(self), UserSlot(adv),
 *     plus one input pin per UPROPERTY on the selected struct (parent fields included).
 * - Synthetic callsite: the node injects File="<BlueprintPath>:<NodeGuid>", Line=0,
 *   Function=<enclosing-graph-name> as literals into the call.
 */
UCLASS()
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Analytics_SendEvent : public UK2Node
{
	GENERATED_BODY()

public:
	/**
	 * The event type chosen from the dropdown; drives dynamic pin allocation.
	 *
	 * `MetaStruct` filters the property picker so only USTRUCTs deriving from
	 * FBeamAnalyticsEvent are listed. The picker still shows the base FBeamAnalyticsEvent
	 * itself, but selecting it produces a node with no input pins (no fields), which
	 * is harmless.
	 */
	UPROPERTY(EditAnywhere, Category="Analytics",
		meta=(MetaStruct="/Script/BeamableCore.BeamAnalyticsEvent"))
	TObjectPtr<UScriptStruct> SelectedEventType = nullptr;

	// UEdGraphNode
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetMenuCategory() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual bool IsNodeSafeToIgnore() const override { return true; }
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	/** Required for the Details panel to display SelectedEventType when the node is selected. */
	virtual bool ShouldShowNodeProperties() const override { return true; }

private:
	static const FName PN_ContextObject;
	static const FName PN_UserSlot;
	static const FName PN_Result;

	/** Per-event-field input pins generated from SelectedEventType. */
	void CreatePinsForEventType();

	/** Builds the synthetic callsite strings used at expand time. */
	void BuildCallsiteLiterals(FString& OutFile, int32& OutLine, FString& OutFunction) const;
};
