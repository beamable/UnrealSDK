// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "BeamBallAssetManager.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBeamContentLoaded, UObject*, asset);

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBeamContentLoadedCode, UObject*, asset);

/**
 * 
 */
UCLASS()
class BEAMPROJ_BEAMBALL_API UBeamBallAssetManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	TMap<FString, UObject*> LoadedAssets;

	TMap<FString, TArray<FOnBeamContentLoaded>> OnContentLoaded;
	TMap<FString, TArray<FOnBeamContentLoadedCode>> OnContentLoadedCode;
	
public:
	UFUNCTION(BlueprintCallable)
	void CacheAsset(FString Key, UObject* Asset);

	UFUNCTION(BlueprintCallable)
	void GetLoadedAssets(FString Key, FOnBeamContentLoaded OnLoadedAsset);

	void GetLoadedAssets(FString Key, FOnBeamContentLoadedCode OnLoadedAsset);
};
