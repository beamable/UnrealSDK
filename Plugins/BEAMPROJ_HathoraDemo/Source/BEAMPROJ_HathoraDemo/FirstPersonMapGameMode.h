// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstPersonDemoPlayerState.h"
#include "HathoraSDK.h"
#include "HathoraSDKRoomV2.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/BeamRuntime.h"
#include "Subsystems/Lobby/BeamLobbySubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "FirstPersonMapGameMode.generated.h"

DECLARE_DELEGATE_OneParam(FRefreshCurrentLobbyDelegate, bool);

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMPROJ_HATHORADEMO_API AFirstPersonMapGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamLobbySubsystem* LobbySubsystem;

	UPROPERTY()
	UBeamStatsSubsystem* StatsSubsystem;

	UPROPERTY()
	FGuid CurrentLobbyId;

	UPROPERTY()
	ULobby* CurrentLobby;

	UPROPERTY()
	bool bNotInHathora;

	virtual void BeginPlay() override
	{
		if (!GetWorld()->IsNetMode(NM_DedicatedServer))
		{
			return;
		}

		const auto* GameInstance = GetGameInstance();
		if (!IsValid(GameInstance))
		{
			UE_LOG(LogTemp, Error, TEXT("AServerActor::BeginPlay -- Invalid GameInstance"));
			return;
		}

		// get UBeamRuntime subsystem
		auto* BeamRuntime = GameInstance->GetSubsystem<UBeamRuntime>();
		if (!IsValid(BeamRuntime))
		{
			UE_LOG(LogTemp, Error, TEXT("AServerActor::BeginPlay -- Invalid BeamRuntime"));
			return;
		}

		FRuntimeStateChangedHandler OnStartedHandler;
		OnStartedHandler.BindDynamic(this, &ThisClass::OnBeamableStarted);
		BeamRuntime->RegisterOnStarted(OnStartedHandler);
	}

	virtual void PreLoginAsync(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, const FOnPreLoginCompleteDelegate& OnComplete) override
	{
		// In PIE, we have no guards on letting players connect 
		if (GetWorld()->IsPlayInEditor())
		{
			OnComplete.Execute("");
			return;
		}

		// In deployed services, we don't let people join while we are fetching the lobby.
		if (!CurrentLobby)
		{
			OnComplete.Execute("Lobby not ready!");
			return;
		}

		// After we have the lobby, we only let in players that are in the lobby.
		const auto GamerTag = FBeamGamerTag{UniqueId.ToString()};
		bool bFoundPlayer = false;
		for (ULobbyPlayer* Val : CurrentLobby->Players.Val)
		{
			const auto playerTag = Val->PlayerId.Val;
			bFoundPlayer = playerTag == GamerTag;
		}

		if (!bFoundPlayer)
			OnComplete.Execute("User not found in lobby");
		else
			OnComplete.Execute("User not found in lobby");
	}

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override
	{
		auto PlayerState = NewPlayerController->GetPlayerState<AFirstPersonDemoPlayerState>();
		PlayerState->PlayerHP = 4.0f;

		// Code that runs on the actual dedicated server (it is capable of actually getting 
		if (!GetWorld()->IsPlayInEditor())
		{
			NewPlayerController->GetPlayerState<AFirstPersonDemoPlayerState>()->BeamableGamerTag = UniqueId.ToString();
			return TEXT("");
		}

		// Code that runs only in PIE for handling initializing state locally without a Hathora instance during development.
		PlayerState->BeamableGamerTag = UniqueId.ToString();
		return TEXT("");
	}

	UFUNCTION()
	void OnBeamableStarted()
	{
		// log
		UE_LOG(LogTemp, Log, TEXT("AServerActor::OnBeamableStarted -- Beamable Started"));
		LobbySubsystem = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
		StatsSubsystem = GetGameInstance()->GetSubsystem<UBeamStatsSubsystem>();
		StatsSubsystem->OnStatsUpdatedCode.AddUObject(this, &ThisClass::OnStatsUpdated);

		const auto ProcessId = FPlatformMisc::GetEnvironmentVariable(TEXT("HATHORA_PROCESS_ID"));
		UE_LOG(LogTemp, Log, TEXT("AServerActor::OnBeamableLoginOperationComplete -- Pid: %s"), *ProcessId);

		FString appId;
		FString DevToken;

		GConfig->GetString(TEXT("HathoraSDK"), TEXT("AppId"), appId, GEngineIni);
		GConfig->GetString(TEXT("HathoraSDK"), TEXT("DevToken"), DevToken, GEngineIni);
		FHathoraSDK::Instance()->SetCredentials(appId, FHathoraSDKSecurity(DevToken));

		auto* Rooms = FHathoraSDK::Instance()->RoomV2;

		const auto GetRoomIdsHandler = FHathoraSDKRoomV2::FHathoraOnGetRoomsForProcess::CreateUObject(this, &ThisClass::OnGetRoomsForProcessCompleted);
		Rooms->GetActiveRoomsForProcess(ProcessId, GetRoomIdsHandler);
	}

	// Called every frame
	virtual void Tick(float DeltaTime) override
	{
		Super::Tick(DeltaTime);
	}

	void OnGetRoomsForProcessCompleted(FHathoraGetRoomsForProcessResult Result)
	{
		// log Result
		UE_LOG(LogTemp, Log, TEXT("AServerActor::OnGetRoomsForProcessCompleted -- Result: %d ErrorMessage:%s"), Result.StatusCode, *Result.ErrorMessage);

		if (Result.Data.Num() > 0)
		{
			if (!IsValid(LobbySubsystem))
			{
				UE_LOG(LogTemp, Error, TEXT("AServerActor::OnGetRoomsForProcessCompleted -- Invalid LobbySubsystem"));
				return;
			}

			auto RoomData = Result.Data[0];
			if (!FGuid::Parse(RoomData.RoomId, CurrentLobbyId))
			{
				UE_LOG(LogTemp, Error, TEXT("AServerActor::OnGetRoomsForProcessCompleted -- Failed to parse LobbyId: %s"), *RoomData.RoomId);
				return;
			}

			UE_LOG(LogTemp, Log, TEXT("AServerActor::OnGetRoomsForProcessCompleted -- LobbyId: %s"), *CurrentLobbyId.ToString());

			auto Handler = FRefreshCurrentLobbyDelegate::CreateLambda([this](bool Success)
			{
				// log server time
				UE_LOG(LogTemp, Log, TEXT("AServerActor::OnGetRoomsForProcessCompleted -- ServerTime: %f"), UGameplayStatics::GetRealTimeSeconds(this));
			});

			UE_LOG(LogTemp, Log, TEXT("AServerActor::OnGetRoomsForProcessCompleted --  Calling RefreshCurrentLobby ServerTime: %f"), UGameplayStatics::GetRealTimeSeconds(this));
			RefreshCurrentLobby(Handler);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("AServerActor::OnGetRoomsForProcessCompleted -- No active rooms found"));
			bNotInHathora = true;
		}
	}


	void OnStatsUpdated(FBeamStatsUpdatedEvent Event)
	{
		// log OnStatsUpdated
		UE_LOG(LogTemp, Log, TEXT("AServerActor::OnStatsUpdated -- StatsUpdatedEvent: %s"), *Event.GamerTag.AsString);
	}


	void RefreshCurrentLobby(FRefreshCurrentLobbyDelegate& Callback)
	{
		if (!IsValid(LobbySubsystem))
		{
			UE_LOG(LogTemp, Error, TEXT("AServerActor::RefreshCurrentLobby -- Invalid LobbySubsystem"));
			return;
		}

		const auto Handler = FBeamOperationEventHandlerCode::CreateLambda([this, Callback](FBeamOperationEvent BeamOperationEvent)
		{
			UE_LOG(LogTemp, Log, TEXT("AServerActor::RefreshCurrentLobby -- TryGetLobby: %s"), *CurrentLobbyId.ToString());

			if (!LobbySubsystem->TryGetLobbyById(CurrentLobbyId, CurrentLobby))
			{
				UE_LOG(LogTemp, Error, TEXT("AServerActor::RefreshCurrentLobby -- Failed to get Lobby: %s"), *CurrentLobbyId.ToString());
				Callback.ExecuteIfBound(false);
			}

			Callback.ExecuteIfBound(true);
		});

		LobbySubsystem->CPP_RefreshLobbyDataOperation(GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot(), Handler, CurrentLobbyId);
	}
};
