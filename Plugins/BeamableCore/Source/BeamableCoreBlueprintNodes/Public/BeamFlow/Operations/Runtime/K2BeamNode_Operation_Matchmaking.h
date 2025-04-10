// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"

#include "K2BeamNode_Operation_Matchmaking.generated.h"

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_TryJoinQueue"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_TryJoinQueue : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beam - Operation - Matchmaking - Join Queue"); }

	virtual FString GetServiceName() const override { return FString("Matchmaking"); };
	
	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, TryJoinQueueOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_TryJoinQueueWithTags"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_TryJoinQueueWithTags : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beam - Operation - Matchmaking - Join Queue with Tags"); }

	virtual FString GetServiceName() const override { return FString("Matchmaking"); };
	
	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, TryJoinQueueWithTagsOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_TryLeaveQueue"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_TryLeaveQueue : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beam - Operation - Matchmaking - Leave Queue"); }

	virtual FString GetServiceName() const override { return FString("Matchmaking"); };
	
	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, TryLeaveQueueOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
