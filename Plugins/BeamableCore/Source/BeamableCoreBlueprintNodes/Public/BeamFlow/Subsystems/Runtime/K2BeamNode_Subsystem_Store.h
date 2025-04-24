// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Store/BeamStoreSubsystem.h"
#include "K2BeamNode_Subsystem_Store.generated.h"
//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetStoreView"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetStoreView : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Store - TryGetStoreView"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, TryGetStoreView); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamStoreSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_PerformPurchase"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_PerformPurchase : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Store - Perform Purchase"); }

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

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Store - Refresh Store"); }

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

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Store - Refresh Stores"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamStoreSubsystem, RefreshStoresOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamStoreSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
