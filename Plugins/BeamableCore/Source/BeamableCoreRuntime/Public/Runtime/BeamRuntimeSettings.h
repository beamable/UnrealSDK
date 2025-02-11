// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfBeamContentId.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Engine/StreamableManager.h"


#include "BeamRuntimeSettings.generated.h"
class UBeamContentCache;
class UDataTable;
class UBeamRuntimeSubsystem;
class UBeamContentObject;

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
	 * @brief List of all the subsystems that is not needed to be initialized at the game start.
	 * By adding subsystems to this list they will not be initialized at the game start however these subsystems could be
	 * initialized later by calling ManuallyInitializeSubsystems Function at BeamRuntime
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Beam Systems")
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
	 * @brief Specify filters for which content to download when bDownloadIndividualContentOnStart is true. This has 3 cases:
	 * - If the content type is NOT listed in this map OR it IS listed but the FOptionalArrayOfBeamContentId is NOT set, we download all the content of that type.
	 * - If the content type IS listed in this map and FOptionalArrayOfBeamContentId is set as an Empty array, we download NONE of the content of that type.
	 * - If the content type IS listed in this map and FOptionalArrayOfBeamContentId is set as an non-Empty array, we download ONLY of the content of that type that matches the IDs in the array.
	 *
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Content")
	TMap<TSubclassOf<UBeamContentObject>, FOptionalArrayOfBeamContentId> IndividualContentDownloadFilter = {};


	FStreamableManager& GetStreamableManager() { return ContentStreamingManager; }

	/**
	 * @brief Before marking a UserSlot as in CONN_Offline status, we'll attempt to reconnect this amount of times.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Connectivity")
	int ConnectivityRetryCountBeforeOffline = 1;

	/**
	 * @brief CONN_Fixup is an intermediate state for when you reconnect. For complex reconnection flows, it can be necessary something more than just a "reconnected" callback.
	 * However, in simple cases, a "reconnected" callback is sufficient.
	 * For those cases, set this to true so that we leave the CONN_Fixup state and go back into CONN_Online immediately after running the callback.
	 *
	 * When this is false, you must call UBeamConnectivityManager::NotifyFixupComplete at some point in your own code.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Connectivity")
	bool AutomaticallyNotifyFixupComplete = true;

};
