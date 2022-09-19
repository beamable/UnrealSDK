// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"
#include "BeamEnvironment.h"
#include "UObject/Object.h"
#include "BeamCoreSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="My Settings"))
class BEAMABLECORE_API UBeamCoreSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBeamCoreSettings();

	/* Soft path will be converted to content reference before use */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TSoftObjectPtr<UBeamEnvironmentData> RuntimeEnvironment;

	/* Soft path will be converted to content reference before use */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TSoftObjectPtr<UBeamEnvironmentData> EditorEnvironment;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	bool AlwaysRunGlobalErrorHandlers = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	bool AlwaysLogSuccessResponses = true;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	bool AlwaysLogErrorResponses = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	bool AlwaysLogCompletedResponses = true;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	FBeamRetryConfig FallbackRetryConfiguration{10, {.5f, 1, 2, 4, 8}, 5};
};
