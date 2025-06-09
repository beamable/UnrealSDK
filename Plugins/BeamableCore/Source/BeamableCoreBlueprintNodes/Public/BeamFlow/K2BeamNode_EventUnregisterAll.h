// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2BeamNode_EventRegister.h"
#include "K2BeamNode_EventUnregister.h"
#include "K2BeamNode_EventUnregisterAll.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable, NotBlueprintType, Hidden, meta=(EventRegister))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_EventUnregisterAll : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

public:
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	/**
	 *  Get the menu category that will appears on the search node
	 */
	virtual FText GetMenuCategory() const override
	{
		FString Category = FString::Printf(TEXT("Beam|%s|Events"), *GetServiceName());
		return FText::FromString(Category);
	};

	//UK2Node impl
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual UObject* GetJumpTargetForDoubleClick() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual bool ShouldShowNodeProperties() const override { return true; }
	//BeamFlowNode impl

	/**
	 * @brief The UClass for a subsystem (GameInstanceSubsystem or BeamRuntimeSubsystem) that this function resides in. 
	 */
	virtual UClass* GetRuntimeSubsystemClass() const override;

protected:
	/**
	 * @brief The subsystem's GetSelf function name that we can use to call a function on it.
	 * See default implementation to override it correctly.  
	 */
	virtual FName GetSubsystemSelfFunctionName() const;


	virtual bool IsValidProperty(FMulticastDelegateProperty* DelegateProp) override;
};
