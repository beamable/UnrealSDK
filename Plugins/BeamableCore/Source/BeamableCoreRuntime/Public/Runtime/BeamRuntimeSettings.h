// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BeamRuntimeSettings.generated.h"

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
	 * @brief References to all 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Beam Systems")
	TArray<TSubclassOf<USubsystem>> BeamRuntimeSubsystemBlueprints;
};
