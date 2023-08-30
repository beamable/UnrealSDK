// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"


#include "BeamRuntimeSettings.generated.h"
class UBeamContentCache;
class UDataTable;
/**
 * 
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Beamable Runtime"))
class BEAMABLECORERUNTIME_API UBeamRuntimeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBeamRuntimeSettings();


	/**
	 * @brief References to all Blueprint-first Runtime Subsystems that exist (will get created in both Client/Game/Server builds). 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Beam Systems")
	TArray<TSubclassOf<USubsystem>> RuntimeSubsystemBlueprints;

	/**
	 * @brief References to all Blueprint-first Runtime Subsystems that exist (will get created in Server builds --- only). 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Beam Systems")
	TArray<TSubclassOf<USubsystem>> ServerOnlyRuntimeSubsystemBlueprints;

	/**
	 * @brief References to all Blueprint-first Runtime Subsystems that exist (will get created in Client/Game builds --- only). 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Beam Systems")
	TArray<TSubclassOf<USubsystem>> ClientRuntimeSubsystemBlueprints;

	/**
	 * @brief As per UE docs, we have a streamable manager declared to load up beamable content asynchronously at runtime: https://docs.unrealengine.com/5.1/en-US/asynchronous-asset-loading-in-unreal-engine/.
	 */
	FStreamableManager ContentStreamingManager = {};

	/**
	 * @brief Whether or not we should download each individual content JSON when beamable is ready for use.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Content")
	bool bDownloadIndividualContentOnStart = false;	


	FStreamableManager& GetStreamableManager() { return ContentStreamingManager; }
};
