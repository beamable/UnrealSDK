// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamK2.h"
#include "K2BeamNode_EventRegister.h"
#include "K2BeamNode_EventUnregister.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable, NotBlueprintType, Hidden, meta=(EventRegister))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_EventUnregister : public UK2Node
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<FName, bool> EventPins = TMap<FName, bool>();

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	/**
	 *  Get the menu category that will appears on the search node
	 */
	virtual FText GetMenuCategory() const override
	{
		FString Category = FString::Printf(TEXT("Beam|%s|Events"), *GetServiceName());
		return FText::FromString(Category);
	};

	virtual FString GetServiceName() const
	{
		// In order to have the service name we are extract it from the name of the subsystem removing the Beam and Subsystem words from the name.
		// E.g BeamInventorySubsystem will become only Inventory.
		// If this pattern don't match with the case override this.
		FString Name = GetRuntimeSubsystemClass()->GetName();
		Name = Name.Replace(TEXT("Beam"), TEXT(""));
		Name = Name.Replace(TEXT("Subsystem"), TEXT(""));
		return Name;
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
	virtual UClass* GetRuntimeSubsystemClass() const;

protected:
	/**
	 * @brief The subsystem's GetSelf function name that we can use to call a function on it.
	 * See default implementation to override it correctly.  
	 */
	virtual FName GetSubsystemSelfFunctionName() const;


	virtual bool IsValidProperty(FMulticastDelegateProperty* DelegateProp);
};
