// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HathoraTypes.h"
#include "Subsystems/Matchmaking/BeamMatchmakingHooks.h"
#include "BeamBallMatchmakingHooks.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BEAMPROJ_BEAMBALL_API UBeamBallMatchmakingHooks : public UBeamMatchmakingHooks
{
	GENERATED_BODY()

public:
	// virtual void UpdatePings_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle) override;
	//
	// void OnUpdatePings(FHathoraRegionPings Result, UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);
};
