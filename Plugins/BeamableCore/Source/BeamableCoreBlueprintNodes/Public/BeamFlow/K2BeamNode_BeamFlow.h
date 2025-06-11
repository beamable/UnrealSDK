// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamK2.h"
#include "BlueprintActionDatabaseRegistrar.h"

#include "K2BeamNode_BeamFlow.generated.h"

#define LOCTEXT_NAMESPACE "BeamK2_BeamFlow"

/**
 * 
 */
UCLASS(NotBlueprintable, NotBlueprintType, Hidden, meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_BeamFlow : public UK2Node
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Beam Flow")
	bool bIsInBeamFlowMode = true;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual bool ShouldShowNodeProperties() const override { return true; }

	virtual bool IsNodeSafeToIgnore() const override;
	virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	virtual FText GetMenuCategory() const override;

	virtual FString GetServiceName() const;

	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FName GetCornerIcon() const override;

	virtual UObject* GetJumpTargetForDoubleClick() const override;

	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	void ExitBeamFlowMode();
	void EnterBeamFlowMode();

	virtual void ExitBeamFlowModeImpl();
	virtual void EnterBeamFlowModeImpl();
};

#undef LOCTEXT_NAMESPACE
