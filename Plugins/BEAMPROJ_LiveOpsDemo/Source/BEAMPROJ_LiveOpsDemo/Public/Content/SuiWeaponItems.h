// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamItemContent.h"
#include "SuiWeaponItems.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMPROJ_LIVEOPSDEMO_API USuiWeaponItems : public UBeamItemContent
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void GetContentType_USuiWeaponItems(FString& Result){ Result = TEXT("weapon"); }

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName name;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString description;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString image;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<FString, FString> customProperties;
};