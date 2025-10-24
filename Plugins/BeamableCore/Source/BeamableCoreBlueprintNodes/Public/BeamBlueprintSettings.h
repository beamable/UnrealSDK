// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Engine/DeveloperSettings.h"
#include "BeamBlueprintSettings.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FSubEvent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category="Sub Event")
	FString SubEventName;
	
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category="Sub Event", meta=(MustImplement="BeamOperationEventData"))
	TSoftClassPtr<UObject> CastClass;
};

USTRUCT(Blueprintable, BlueprintType)
struct FSubEventArray
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category="Sub Event")
	TArray<FSubEvent> SubEvents;
};

/**
 * 
 */
UCLASS(config=BeamBlueprint, defaultconfig, meta=(DisplayName="Beamable Blueprint"))
class BEAMABLECOREBLUEPRINTNODES_API UBeamBlueprintSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBeamBlueprintSettings();
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Beam SubEvents")
	TMap<TSubclassOf<UK2BeamNode_Operation>, FSubEventArray> Config;

};

