// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PIE/BeamPIE_Utilities.h"
#include "Subsystems/Lobby/BeamLobbySubsystem.h"
#include "Subsystems/PIE/BeamPIE.h"
#include "BeamPIEGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API ABeamPIEGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void PreLoginAsync(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, const FOnPreLoginCompleteDelegate& OnComplete) override
	{
		Super::PreLoginAsync(Options, Address, UniqueId, OnComplete);
	}
};
