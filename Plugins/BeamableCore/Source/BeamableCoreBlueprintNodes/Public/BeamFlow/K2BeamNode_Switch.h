// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectTools.h"
#include "BeamFlow/K2BeamNode_BeamFlow.h"

#include "K2BeamNode_Switch.generated.h"

/**
 * 
 */
#define LOCTEXT_NAMESPACE "K2BeamNode_Switch"

UCLASS()
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Switch : public UK2Node, public IK2Node_AddPinInterface
{
	GENERATED_BODY()

	UPROPERTY()
	int32 InputsNum;

	UPROPERTY()
	TMap<FName, FString> DefaultValue;

	const FName InputPinName = FName("Input");
	const FName OutputPinName = FName("Default Output");

public:
	/**
	 *  Get the menu category that will appears on the search node
	 */
	virtual FText GetMenuCategory() const override
	{
		FString Category = FString::Printf(TEXT("Beam|Switch"));
		return FText::FromString(Category);
	};

	virtual FString GetServiceName() const
	{
		return "Utility";
	};


	virtual FText GetTooltipText() const override
	{
		return Super::GetTooltipText();
	}

	//UK2Node impl
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PostReconstructNode() override;
	virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;
	//BeamFlowNode impl

	virtual FName GetPinName(int32 PinIndex) const;

	// AddPinInterface
	virtual void AddInputPin() override;
	virtual void RemoveInputPin(UEdGraphPin* Pin) override;
	// AddPinInterface

protected:
	UEdGraphPin* GetInputPin() const;
	UEdGraphPin* GetDefaultOutputPin() const;

	void UpdateWildcardPinsType() const;

	static FName GetClassExecPinName(const UClass* Class)
	{
		return FName(FString::Printf(TEXT("On %s"), *Class->GetName()));
	}

	static FName GetClassOutputPinName(const UClass* Class)
	{
		return FName(FString::Printf(TEXT("%s Output"), *Class->GetName()));
	}

	static FName GetClassInputPinName(int32 Index)
	{
		return FName(FString::Printf(TEXT("%d Input"), Index));
	}
};
#undef LOCTEXT_NAMESPACE
