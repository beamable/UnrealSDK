// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Store/BeamStoreSubsystem.h"
#include "K2BeamNode_Operation_Store.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_StorePerformPurchase"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_StorePerformPurchase : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Store - PerformPurchase"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, CommitPurchaseListingOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamStoreSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
