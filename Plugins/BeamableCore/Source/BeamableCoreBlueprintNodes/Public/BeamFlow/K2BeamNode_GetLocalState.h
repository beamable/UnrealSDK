// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_BeamFlow.h"
#include "K2BeamNode_GetLocalState.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable, NotBlueprintType, Hidden, meta=(BeamGetLocalState))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_GetLocalState : public UK2Node
{
	GENERATED_BODY()

	const FName NAME_IsValidExec = FName("Success");
	const FName NAME_IsNotValidExec = FName("Failure");

	UPROPERTY()
	TArray<FString> WrappedOperationFunctionInputPinNames;

	UPROPERTY()
	TArray<FString> WrappedOperationFunctionOutputPinNames;

public:
	
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	
	virtual FText GetMenuCategory() const override
	{
		FString Category = FString::Printf(TEXT("Beam|%s|GetState"), *GetServiceName());
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

	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	//BeamFlowNode impl

protected:
	/**
	 * @brief The subsystem's GetSelf function name that we can use to call a function on it.
	 * See default implementation to override it correctly.  
	 */
	virtual FName GetSubsystemSelfFunctionName() const;

	/**
	 * @brief The subsystem's function.
	 */
	virtual FName GetFunctionName() const;

	/**
	 * @brief The UClass for a subsystem (GameInstanceSubsystem or BeamRuntimeSubsystem) that this function resides in. 
	 */
	virtual UClass* GetRuntimeSubsystemClass() const;

	/**
	 * @brief The filter function to ignore the output pin of boolean type
	 */
	static bool IsIgnoredPinOfReturnBoolType(const UEdGraphNode* EdGraphNode, const FProperty* Param);
};
