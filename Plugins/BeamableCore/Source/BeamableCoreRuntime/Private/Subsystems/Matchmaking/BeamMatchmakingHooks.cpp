// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Matchmaking/BeamMatchmakingHooks.h"

#include "RequestTracker/BeamOperationHandle.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"

void UBeamMatchmakingHooks::PreTryJoinQueue_Implementation(UBeamHookHandle* MatchmakingHookHandle)
{
	GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(MatchmakingHookHandle->CurrentOperationHandle, "Success");
}

void UBeamMatchmakingHooks::TryJoinQueue_Implementation(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op)
{
	GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, "Success");
}

void UBeamDefaultMatchmakingHooks::TryJoinQueue_Implementation(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op)
{
	auto GInstance = Context->GetWorld()->GetGameInstance();
	auto MatchmakingSubsystem = GInstance->GetSubsystem<UBeamMatchmakingSubsystem>();
	MatchmakingSubsystem->TryJoinQueue(Slot, GameTypeQueue, Team, Tags, Op);
}
