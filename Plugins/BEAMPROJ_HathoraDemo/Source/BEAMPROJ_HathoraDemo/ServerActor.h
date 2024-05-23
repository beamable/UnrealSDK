// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HathoraSDKRoomV2.h"
#include "GameFramework/Actor.h"
#include "Subsystems/Lobby/BeamLobbySubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "ServerActor.generated.h"

DECLARE_DELEGATE_OneParam(FRefreshCurrentLobbyDelegate, bool);


UCLASS()
class BEAMPROJ_HATHORADEMO_API AServerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AServerActor();

	UPROPERTY()
	UBeamLobbySubsystem* LobbySubsystem;

	UPROPERTY()
	UBeamStatsSubsystem* StatsSubsystem;

	UPROPERTY()
	FGuid CurrentLobbyId;

	UPROPERTY()
	ULobby* CurrentLobby;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
	void OnBeamableStarted();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void OnGetRoomsForProcessCompleted(FHathoraGetRoomsForProcessResult Result);	
	void OnStatsUpdated(FBeamStatsUpdatedEvent Event);	
	void RefreshCurrentLobby(FRefreshCurrentLobbyDelegate& Callback);
};
