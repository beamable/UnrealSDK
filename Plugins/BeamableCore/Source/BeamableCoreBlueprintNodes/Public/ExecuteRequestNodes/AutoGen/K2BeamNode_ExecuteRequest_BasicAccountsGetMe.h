// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KismetCompiler.h"
#include "K2Node_CallFunction.h"

#include "K2BeamNode_ExecuteRequest_BasicAccountsGetMe.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ExecuteRequest_BasicAccountsGetMe"


/**
 * 
 */
UCLASS(meta=(BeamFlow))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_ExecuteRequest_BasicAccountsGetMe : public UK2Node
{
	GENERATED_BODY()
public:
	static const FName SelfFunctionName;
	static const FName RequestFunctionName;
	static const FName MakeFunctionName;


	UPROPERTY()
	TArray<FString> WrappedRequestFunctionPinNames;

	UPROPERTY()
	TArray<FString> WrappedMakeFunctionPinNames;

	UPROPERTY()
	bool bIsInBeamFlowMode = true;

	virtual bool IsNodeSafeToIgnore() const override;
	virtual bool IsCompatibleWithGraph(UEdGraph const* Graph) const override;

	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;


	virtual FText GetMenuCategory() const override;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual void AllocateDefaultPins() override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FName GetCornerIcon() const override;

	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	void ExitBeamFlowMode();
	void EnterBeamFlowMode();	

private:
};

#undef LOCTEXT_NAMESPACE
