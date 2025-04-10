// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Store/BeamStoreSubsystem.h"
#include "K2BeamNode_Operation_Store.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_PerformPurchase"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_PerformPurchase : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beam - Operation - Store - Perform Purchase"); }

	virtual FString GetServiceName() const override { return FString("Store"); };
	
	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, PerformPurchaseOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamStoreSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_RefreshStore"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_RefreshStore : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beam - Operation - Store - Refresh Store"); }

	virtual FString GetServiceName() const override { return FString("Store"); };
	
	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, RefreshStoreOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamStoreSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_RefreshStores"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_RefreshStores : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beam - Operation - Store - Refresh Stores"); }

	virtual FString GetServiceName() const override { return FString("Store"); };
	
	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, RefreshStoresOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamStoreSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE