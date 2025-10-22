// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Matchmaking/BeamMatchmakingHooks.h"

#include "RequestTracker/BeamOperationHandle.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"


void UBeamMatchmakingHooks::SetContext(const UObject* ContextReference)
{
	this->Context = ContextReference;
}

void UBeamMatchmakingHooks::UpdatePings_Implementation(UBeamMatchmakingHookHandle* MatchmakingHookHandle)
{
	GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccessWithData(MatchmakingHookHandle->OperationHandle, "Success", MatchmakingHookHandle);
}

void UBeamMatchmakingHooks::TryJoinQueue_Implementation(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op)
{
	
}

void UBeamMatchmakingHooks::TryJoinQueueHookAction_Implementation(UBeamMatchmakingHookHandle* MatchmakingHookHandle)
{
	
}

