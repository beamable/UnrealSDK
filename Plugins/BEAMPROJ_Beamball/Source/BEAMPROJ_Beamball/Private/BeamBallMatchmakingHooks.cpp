// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBallMatchmakingHooks.h"

#include "HathoraSDK.h"
#include "RequestTracker/BeamRequestTracker.h"


// void UBeamBallMatchmakingHooks::UpdatePings_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle)
// {
// 	FHathoraSDK::Instance()->GetRegionalPings(FHathoraOnGetRegionalPings::CreateUObject(this, &UBeamBallMatchmakingHooks::OnUpdatePings, MatchmakingHookHandle));
// }
//
// void UBeamBallMatchmakingHooks::OnUpdatePings(FHathoraRegionPings Result, UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle)
// {
// 	MatchmakingHookHandle->PingsPerRegion = Result.Pings;
// 	GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccessWithData(MatchmakingHookHandle->CurrentOperationHandle, "Success", MatchmakingHookHandle);
// }
