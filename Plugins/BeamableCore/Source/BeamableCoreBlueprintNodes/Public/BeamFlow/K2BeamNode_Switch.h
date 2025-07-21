// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectTools.h"
#include "BeamFlow/K2BeamNode_BeamFlow.h"

#include "K2BeamNode_Switch.generated.h"

USTRUCT()
struct FSwitchClassInputPin
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGuid Guid;

	UPROPERTY()
	FString DefaultValue;

	FSwitchClassInputPin(FGuid Guid, FString DefaultValue)
		: Guid(Guid),
		  DefaultValue(DefaultValue)
	{
	}

	FSwitchClassInputPin() = default;
};


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
	TArray<FGuid> WildcardsPins;

	// UPROPERTY()
	// TMap<FName, FString> DefaultValue;

	UPROPERTY()
	TArray<FSwitchClassInputPin> ClassInputPins;

	const FName InputPinName = FName("Object");
	const FName OutputPinName = FName("Cast Failed - Object");
	const FName FriendlyPassThrough = FName("PassThrough");
	const FName FriendlyPassThroughOutput = FName("PassThrough - Output");

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
	void InteractiveAddWildcardInputPin();
	void InteractiveRemoveWildcardInputPin(UEdGraphPin* EdGraphPin);
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
	virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PostReconstructNode() override;
	virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;
	//BeamFlowNode impl

	// AddPinInterface
	virtual void AddInputPin() override;
	virtual void RemoveInputPin(UEdGraphPin* Pin) override;
	// AddPinInterface

protected:
	UEdGraphPin* GetInputPin() const;
	UEdGraphPin* GetDefaultOutputPin() const;

	void UpdateWildcardPinsType() const;

	static FName GetOutputWildcardPinName(const FGuid Guid)
	{
		return FName(Guid.ToString() + "Output");
	}

	static FName GetInputWildcardPinName(const FGuid Guid)
	{
		return FName(Guid.ToString());
	}

	static FName GetClassExecPinName(const UClass* Class)
	{
		return FName(FString::Printf(TEXT("Cast To %s"), *Class->GetName()));
	}

	static FName GetClassOutputPinName(const UClass* Class)
	{
		return FName(FString::Printf(TEXT("As %s"), *Class->GetName()));
	}

	static FName GetClassInputPinName(int32 Index)
	{
		return FName(FString::Printf(TEXT("Cast Class %d"), Index));
	}
};
#undef LOCTEXT_NAMESPACE
