// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Matchmaking/BeamMatchmakingHooks.h"

#include "RequestTracker/BeamRequestTracker.h"

void UBeamMatchmakingHooks::UpdatePings_Implementation(UBeamMatchmakingHookHandle* MatchmakingHookHandle)
{
	MatchmakingHookHandle->PingsPerRegion = TMap<FString, int32>();

	GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccessWithData(MatchmakingHookHandle->OperationHandle, "Success", MatchmakingHookHandle);
}
