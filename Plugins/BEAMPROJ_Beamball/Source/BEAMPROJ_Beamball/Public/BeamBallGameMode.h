// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/PlayerState.h"
#include "Runtime/BeamMultiplayer.h"
#include "Subsystems/PIE/BeamPIE.h"
#include "BeamBallGameMode.generated.h"


UCLASS()
class UBeamBallLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:
	virtual FString GetGameLoginOptions() const override
	{
		return BeamMultiplayer::LocalPlayer::GetGameLoginOptions(this, Super::GetGameLoginOptions());
	}
};

UCLASS()
class UBeamBallGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void StartGameInstance() override
	{
		BeamPIE::GameInstance::PreStartGameInstance(this);
		Super::StartGameInstance();
		BeamPIE::GameInstance::StartGameInstance(this);
	}

#if WITH_EDITOR
	virtual FGameInstancePIEResult StartPlayInEditorGameInstance(ULocalPlayer* LocalPlayer, const FGameInstancePIEParameters& Params) override
	{
		BeamPIE::GameInstance::StartPlayInEditorGameInstance(this, LocalPlayer, Params);
		return Super::StartPlayInEditorGameInstance(LocalPlayer, Params);
	}
#endif

	virtual bool DelayPendingNetGameTravel() override
	{
		return BeamPIE::GameInstance::DelayPendingNetGameTravel(this);
	}
};

/**
 * 
 */
UCLASS(Blueprintable)
class BEAMPROJ_BEAMBALL_API ABeamBallGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void BeginPlay() override
	{
		// This will run once beamable (you can either call init here OR 
		const auto BeamRuntime = GetGameInstance()->GetSubsystem<UBeamRuntime>();
		BeamRuntime->CPP_RegisterOnStarted(FBeamRuntimeHandlerCode::CreateLambda([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Started!"));
			// If we need to set up our orchestrator... 
			if (BeamPIE::Orchestrator::ShouldRegisterOrchestrator(this))
			{
				// If we have no settings, then we are running in a build.
				UE_LOG(LogTemp, Warning, TEXT("Setting up my orchestrator!!!!"));

				// Let's call RegisterLobbyWithServer so that the Federation becomes aware that the GameServer already has the Beamable lobby data in it.
				// Only after this call succeeds will the Federation notify users that the match was found --- this means that PreLoginAsync is guaranteed to have the lobby data at that point. 
				const auto LobbyId = BeamMultiplayer::Orchestrator::GetLobbyIdFromCLArgs(this);
				BeamMultiplayer::Orchestrator::RegisterLobbyWithServer(this, LobbyId, FBeamOperationEventHandlerCode::CreateLambda([this, LobbyId](FBeamOperationEvent Evt)
				{
					// Failed to get lobby data from Beamable
					// TODO: Handle error by telling Orchestrator to kill the room maybe? 
					if (Evt.CompletedWithError()) return;

					// Got the lobby data from Beamable
					// TODO: Handle success by doing whatever sort of pre-loading of data based on the lobby 
					if (Evt.CompletedWithSuccess())
					{
						const auto Lobbies = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
						ULobby* Lobby;
						if (Lobbies->TryGetLobbyById(LobbyId, Lobby))
						{
							// Do stuff with the lobby
							BeamMultiplayer::Orchestrator::NotifyLobbyReady(this, LobbyId, FBeamOperationEventHandlerCode::CreateLambda([](FBeamOperationEvent Evt)
							{
								// Users will never receive the notification that a match was found, will timeout and get put back into the queue.
								// TODO: Maybe kill the server so it doesn't linger?
								if (Evt.CompletedWithError()) return;

								// Users will start trying to connect soon (PreLoginAsync flow)
								if (Evt.CompletedWithSuccess()) return;
							}));
						}
						else
						{
							// Something went really wrong inside the Lobby Subsystem (report to Beamable)...
						}
					}
				}));
			}
		}));
	}

public:
	virtual void PostLogin(APlayerController* NewPlayer) override
	{
		Super::PostLogin(NewPlayer);
		// TODO: We can ask people to call a node/utility function here so we can make the various GetUserSlotByPlayerController/State work both in the server and in the client.
		// It'll work for as long as we have the UniqueId Mapping options set in RuntimeSettings...
		// When that is turned off, we can emit warnings that these functions will all stop working until you start calling a utility in the Login flow
		// If you do, that utility will ask the RuntimeSubsystem to map the Player's Controller to their GamerTag --- that mapping is used as a fallback in the server to get a
		// FUserSlot that returns true for FUserSlot::IsServerMappingSlot (as well as whenever people ask for a gamertag by uniqueid or player controller).
		// If you don't call this utility, those functions don't work on the server.
		//
		// BeamMultiplayer::PlayerController::PostLogin(NewPlayer);
		// 
		// const auto UniqueIdA = NewPlayer->NetConnection->PlayerId;
		// const auto UniqueIdB = NewPlayer->GetPlayerState<APlayerState>()->GetUniqueId();
		//
		// UE_BEAM_LOG(GEngine->GetWorldContextFromWorld(this->GetWorld()), LogBeamEditor, Warning, TEXT("LoggedIn Id - %s - %s"),
		// 					*UniqueIdA.GetUniqueNetId().Get()->ToString(),
		// 					*UniqueIdB.GetUniqueNetId().Get()->ToString())
	}

	virtual void PreLoginAsync(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, const FOnPreLoginCompleteDelegate& OnComplete) override
	{
		// This enables us to test the Pre-Login in PIE correctly (it adds options so that we can accept users in the expected deterministic order the PIE instances create and connect) 
		const auto BeamOptions = BeamPIE::Authentication::GetExpectedClientPIEOptions(this, Options, Address, UniqueId);

		// Validate that the user coming in is really one that exists in a lobby that has been BeamMultiplayer::Orchestrator::RegisterLobbyWithServer.
		// BeamPIE guarantee's that happens for the lobbies it creats for PIE use.
		BeamMultiplayer::Authentication::PreLoginAsync(this, BeamOptions, Address, UniqueId, FBeamOperationEventHandlerCode::CreateLambda([this, OnComplete, BeamOptions, Address, UniqueId](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				UE_BEAM_LOG(GEngine->GetWorldContextFromWorld(this->GetWorld()), LogBeamEditor, Warning, TEXT("GetPreferredUniqueNetId - 2 - %s"),
				            *UniqueId.GetUniqueNetId().Get()->ToString())
				Super::PreLoginAsync(BeamOptions, Address, UniqueId, OnComplete);
			}

			// If failed, deny entry into the server.
			if (Evt.EventType == OET_ERROR)
			{
				OnComplete.ExecuteIfBound(Evt.EventCode);
			}
		}));
	}

	virtual void Logout(AController* Exiting) override
	{
		Super::Logout(Exiting);
		// TODO: Cleanup UserSlots that are registered when a controller leaves.
	}
};
