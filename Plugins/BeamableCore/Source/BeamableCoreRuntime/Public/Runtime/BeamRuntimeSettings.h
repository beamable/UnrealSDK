// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BeamRuntimeSettings.generated.h"

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
	 * @brief References to all Blueprint-first Runtime Subsystems that exist. 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Beam Systems")
	TArray<TSubclassOf<USubsystem>> BeamRuntimeSubsystemBlueprints;


	/**
	 * @brief References to all cooked content manifests (baked into the builds via cooking process).
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Beam Systems")
	TArray<TSoftObjectPtr<UDataTable>> CookedManifests;
};
