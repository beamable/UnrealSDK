// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBallSkinDataAsset.h"
#include "Content/BeamContentObject.h"
#include "BeamballSkinItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMBALL_API UBeamballSkinItem : public UBeamContentObject
{
	GENERATED_BODY()
	
public:
	// Define the ContentTypeId for this Type
	UFUNCTION()
	void GetContentType_UBeamballSkinItem(FString& Result){Result = TEXT("itemskin");};
	
	// Define a SoftObjectPath for the skin item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UBeamBallSkinDataAsset> SelectedSkin;
};
