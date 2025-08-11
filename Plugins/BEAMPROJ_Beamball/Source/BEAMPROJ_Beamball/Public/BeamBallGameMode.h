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
			// 3 scenarios:
			// ---- [Deployed build only] One server per instance. The lobby ID should be passed via command line or environment variable. (Consider creating a utility function for this.)
			// ---- [Deployed build only] Multiple instances running on the same server. Every time a new instance is assigned, the game maker must call the register function for that instance.
			// ---- [Editor only — all modes: standalone, client, etc.] During Beam PIE, there's no need to call register manually; the process is handled automatically.

			// Setup Hathora, Agones, GameLyft, whatever you need to extract from your game server orchestrator's SDK, the Beamable Lobby Id your federation gave it.
			// Once you have the lobby
			// const auto LobbySubsystem = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
			// LobbySubsystem->CPP_RegisterLobbyWithServerOperation(FUserSlot{}, {}, {});

			// If we have no settings, then we are running in a build.
			UE_LOG(LogTemp, Warning, TEXT("Setting up my orchestrator!!!!"));
		}
	}

public:
	virtual void PreLoginAsync(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, const FOnPreLoginCompleteDelegate& OnComplete) override
	{
		const auto Lobby = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		const auto ServerSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();


		Lobby->CPP_AcceptUserIntoGameServerOperation(ServerSlot, Options, Address, UniqueId, FBeamOperationEventHandlerCode::CreateLambda([this, OnComplete, Options, Address, UniqueId](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				Super::PreLoginAsync(Options, Address, UniqueId, OnComplete);
			}

			// If failed, deny entry into the server.
			if (Evt.EventType == OET_ERROR)
			{
				OnComplete.ExecuteIfBound(Evt.EventCode);
			}
		}));

		// TODO: We need to make sure this is set up correctly with a sufficiently large value. 
		// https://forums.unrealengine.com/t/where-to-set-connectiontimeout-value/378351/4


		// Beamable works with the default UniqueIds (basically, we do NOT use an OnlineSubsystem to validate the user)
		//   - Way too much noise on those systems.		
		// TODO: When you join the matchmaking queue, party or lobby, we add a property for each player (which is their ULocalPlayer::UniqueNetId)		
		// TODO: If you are using no OnlineSubsystem here in the server, we'll validate via an Option in the travel (LobbyId+AccessToken --- our AcceptUserIntoLobbyOperation will use that
		// token to verify that you are in-fact you and that you are in one of the lobbies this server manages) and just leave the UniqueId untouched.		
		// TODO: If you are using an OnlineSubsystem here in the server, we'll use the UniqueId to validate that the user coming in from Unreal ClientTravel is
		// actually allowed into the server (by comparing with the property in the lobby). This allows you to use whatever subsystem you want to generate the UniqueNetIds and it'll just work with Beamable.
		// But if you want to avoid OnlineSubsystems in servers, you can.

		// Checks if the SDK is initialized, if not --- wait until it is.
		// Then, checks if the provided lobby is in the list of KnownLobbies:
		//   - If it is, validate the user is in it.
		//   - If it isn't, fetch it and then accept the users into it.
		// It must also keep a map of GamerTag to FUniqueNetIdRepl so that we can easily have a way of getting the gamertag from any ULocalPlayer object
		// https://forums.unrealengine.com/t/how-to-pass-a-custom-uniqueid-into-prelogin-from-clienttravel/459527
		// These should be in the lobby itself.

		// Lobby->AcceptUserIntoGameServerOperation(Options, Address, UniqueId, FBeamOperationEventHandlerCode::CreateLambda([Options, Address, UniqueId, OnComplete](FBeamOperationEvent Evt)
		// {
		// 	// If successful, just forward control back to the engine
		// 	if (Evt.EventType == OET_SUCCESS)
		// 	{				
		// 		Super::PreLoginAsync(Options, Address, UniqueId, OnComplete);
		// 	}
		//
		// 	// If failed, deny entry into the server.
		// 	if (Evt.EventType == OET_ERROR)
		// 	{
		// 		OnComplete.ExecuteIfBound(Evt.EventCode);				
		// 	}			
		// }));
	}
};
