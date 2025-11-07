// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hooks/BeamBaseHook.h"
#include "UObject/Object.h"
#include "BeamContentHooks.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamContentHooks : public UBeamBaseHook
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	bool ContentFilter(UBeamIndividualContentDownloadData* BeamContent);
	bool ContentFilter_Implementation(UBeamIndividualContentDownloadData* BeamContent);

	UFUNCTION(BlueprintNativeEvent)
	void OnLoadBeamContent(UBeamIndividualContentDownloadData* BeamContent);
	void OnLoadBeamContent_Implementation(UBeamIndividualContentDownloadData* BeamContent);
};
