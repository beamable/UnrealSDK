// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerActor.h"

#include "HathoraSDK.h"
#include "HathoraSDKRoomV2.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/BeamRuntime.h"


// Sets default values
AServerActor::AServerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AServerActor::BeginPlay()
{
	Super::BeginPlay();
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
	OnStartedHandler.BindDynamic(this, &AServerActor::OnBeamableStarted);
	BeamRuntime->RegisterOnStarted(OnStartedHandler);
}

void AServerActor::OnBeamableStarted()
{
	// log
	UE_LOG(LogTemp, Log, TEXT("AServerActor::OnBeamableStarted -- Beamable Started"));
	LobbySubsystem = GetGameInstance()->GetSubsystem<UBeamLobbySubsystem>();
	StatsSubsystem = GetGameInstance()->GetSubsystem<UBeamStatsSubsystem>();
	StatsSubsystem->OnStatsUpdatedCode.AddUObject(this, &AServerActor::OnStatsUpdated);

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
void AServerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AServerActor::OnGetRoomsForProcessCompleted(FHathoraGetRoomsForProcessResult Result)
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
	}
}

void AServerActor::OnStatsUpdated(FBeamStatsUpdatedEvent Event)
{
	// log OnStatsUpdated
	UE_LOG(LogTemp, Log, TEXT("AServerActor::OnStatsUpdated -- StatsUpdatedEvent: %s"), *Event.GamerTag.AsString);
}

void AServerActor::RefreshCurrentLobby(FRefreshCurrentLobbyDelegate& Callback)
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
