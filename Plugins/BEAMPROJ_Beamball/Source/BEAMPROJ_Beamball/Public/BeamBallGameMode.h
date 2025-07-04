// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Subsystems/PIE/BeamPIE.h"
#include "BeamBallGameMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BEAMPROJ_BEAMBALL_API ABeamBallGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void BeginPlay() override
	{
		// Get the Beam PIE Subsystem to help you set up your orchestrator correctly when running in PIE.  
		const auto PIE = GEngine->GetEngineSubsystem<UBeamPIE>();

		// If we need to set up our orchestrator... 
		if (PIE->RequiresGameServerOrchestratorSetup(this))
		{
			// Setup Hathora, Agones, GameLyft, whatever you need to extract from your game server orchestrator's SDK, the Beamable Lobby Id your federation gave it.
			// Once you have the lobby
			// const auto LobbySubsystem = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
			// LobbySubsystem->CPP_RegisterLobbyWithServerOperation(FUserSlot{}, {}, {});

			// If we have no settings, then we are running in a build.
			UE_LOG(LogTemp, Warning, TEXT("Setting up my orchestrator!!!!"));

		}
	}
};
