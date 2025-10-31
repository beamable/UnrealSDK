// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Matchmaking/BeamMatchmakingHooks.h"

#include "RequestTracker/BeamOperationHandle.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"


void UBeamMatchmakingUpdatePingHook::UpdatePings_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle)
{
	GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(MatchmakingHookHandle->CurrentOperationHandle, "Success");
}

void UBeamMatchmakingTryJoinQueueHook::TryJoinQueue_Implementation(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op)
{
	auto GInstance = Context->GetWorld()->GetGameInstance();
	auto MatchmakingSubsystem = GInstance->GetSubsystem<UBeamMatchmakingSubsystem>();
	MatchmakingSubsystem->TryJoinQueue(Slot, GameTypeQueue, Team, Tags, Op);
}

void UBeamMatchmakingPreTryJoinQueueHook::PreTryJoinQueueHookAction_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle)
{
	
}

void UBeamMatchmakingPreTryJoinQueueHook::PreTryJoinQueueHookActionParallel_Implementation(FBeamOperationHandle MatchmakingHookHandle)
{
	
}

void UBeamMatchmakingAfterTryJoinQueueHook::AfterTryJoinQueueHookAction_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle)
{
	
}

void UBeamMatchmakingAfterTryJoinQueueHook::AfterTryJoinQueueHookActionParallel_Implementation(FBeamOperationHandle MatchmakingHookHandle)
{
	
}

