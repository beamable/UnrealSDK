// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Engine/StreamableManager.h"


#include "BeamRuntimeSettings.generated.h"
class UBeamContentCache;
class UDataTable;
class UBeamRuntimeSubsystem;
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
	 * @brief Whether we should automatically initialize all beamable subsystems on the start of the game play mode.
	 * If you disable this, you will need to call ManuallyInitializeSubsystems Function at BeamRuntime to initialize subsystems when needed
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Beam Systems")
	bool bAutoInitializeSdkAtStartup  = true;

	/**
	 * @brief List of all the subsystems that is not needed to be initialized at the game start.
	 * By adding subsystems to this list they will not be initialized at the game start however these subsystems could be
	 * initialized later by calling ManuallyInitializeSubsystems Function at BeamRuntime
	 */
	UPROPERTY(Config,EditAnywhere, BlueprintReadOnly, Category="Beam Systems")
	TArray<TSubclassOf<UBeamRuntimeSubsystem>> ManualyInitializedRuntimeSubsystems;
	
	/**
	 * @brief As per UE docs, we have a streamable manager declared to load up beamable content asynchronously at runtime: https://docs.unrealengine.com/5.1/en-US/asynchronous-asset-loading-in-unreal-engine/.
	 */
	FStreamableManager ContentStreamingManager = {};

	/**
	 * @brief Whether or not we should download each individual content JSON when beamable is ready for use.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Content")
	bool bDownloadIndividualContentOnStart = false;
	
	/**
	 * @brief Default stores to download by UBeamStoreSubsystem.
	 * If none are specified it will download all the available Stores content.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Content")
	TArray<FBeamContentId> StoreContentToDownload; 
	
	FStreamableManager& GetStreamableManager() { return ContentStreamingManager; }
};
