// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Matchmaking/BeamMatchmakingHooks.h"

#include "RequestTracker/BeamOperationHandle.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"

void UBeamMatchmakingHooks::UpdatePings_Implementation(UBeamMatchmakingHookHandle* MatchmakingHookHandle)
{
	FTimerHandle DelayTimerHandle;
	UWorld* World = MatchmakingHookHandle->Context->GetWorld();
	FTimerDelegate Function = FTimerDelegate::CreateUObject(this, &UBeamMatchmakingHooks::TImer, MatchmakingHookHandle);
	World->GetTimerManager().SetTimer(DelayTimerHandle, Function, 5.0f, false, 3);
	
}

void UBeamMatchmakingHooks::TImer(UBeamMatchmakingHookHandle* MatchmakingHookHandle)
{
	MatchmakingHookHandle->PingsPerRegion = TMap<FString, int32>();
	MatchmakingHookHandle->PingsPerRegion.Add("Sao-Paulo", 20);
	MatchmakingHookHandle->PingsPerRegion.Add("UAE", 150);
	MatchmakingHookHandle->PingsPerRegion.Add("Nordeste", 350);
	GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccessWithData(MatchmakingHookHandle->OperationHandle, "Success", MatchmakingHookHandle);
}
