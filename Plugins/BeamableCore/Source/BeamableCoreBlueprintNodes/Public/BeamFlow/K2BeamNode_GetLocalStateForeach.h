// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamK2.h"
#include "K2BeamNode_GetLocalState.h"
#include "K2BeamNode_GetLocalStateForeach.generated.h"

/**
 * 
 */

UCLASS(NotBlueprintable, NotBlueprintType, Hidden, meta=(BeamGetLocalStateForeach))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_GetLocalStateForeach : public UK2Node
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Get Local State Foreach")
	bool bShowRawArrayMode = false;

	UPROPERTY()
	TArray<FString> WrappedOperationFunctionInputPinNames;

	UPROPERTY()
	TArray<FString> WrappedOperationFunctionOutputPinNames;

	UPROPERTY()
	TArray<FString> WrappedOperationFunctionOutputPinArrayNames;

public:
	virtual FText GetMenuCategory() const override
	{
		FString Category = FString::Printf(TEXT("Beam|%s|LocalState"), *GetServiceName());
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

	virtual FText GetTooltipText() const override
	{
		auto Function = GetRuntimeSubsystemClass()->FindFunctionByName(GetFunctionName());
		FText BaseTooltip = {};
		if (Function != nullptr)
		{
			return FText::FromString(ObjectTools::GetDefaultTooltipForFunction(Function));
		}

		return Super::GetTooltipText();
	}

	//UK2Node impl
	virtual bool ShouldShowNodeProperties() const override { return true; }
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual bool CanJumpToDefinition() const override { return true; };
	virtual void JumpToDefinition() const override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//BeamFlowNode impl

protected:
	virtual FName GetLoopBodyName() { return FName("Loop Body"); }
	virtual FName GetArrayPinName() { return FName("Array"); }
	virtual FName GetBreakPinName() { return FName("Break"); }
	virtual FName GetArrayIndexPinName() { return FName("ArrayIndex"); }
	virtual FName GetCompletedPinName() { return FName("Completed"); }

	UEdGraphPin* GetArrayPin();
	UEdGraphPin* GetBreakPin();
	UEdGraphPin* GetForEachPin();
	UEdGraphPin* GetArrayIndexPin();
	UEdGraphPin* GetCompletedPin();

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
	 * @brief This predicated can be override to hide specific pins in the function
	 */
	virtual BeamK2::CheckParamIsValidForNodePredicate GetIgnoredPinPredicate() const;

	/**
	 * @brief The filter function to ignore the output pin of array type 
	 */
	static bool IsIgnoredPinOfReturnArrayType(const UEdGraphNode* EdGraphNode, const FProperty* Param);

	/**
	 * @brief The filter function to ignore the non array pin type
	 */
	static bool IsIgnoredPinOfReturnNonArrayType(const UEdGraphNode* EdGraphNode, const FProperty* Param);
};
