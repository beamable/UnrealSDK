// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBallSkinDataAsset.h"
#include "Content/BeamContentTypes/BeamItemContent.h"
#include "BeamballSkinItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMBALL_API UBeamballSkinItem : public UBeamItemContent
{
	GENERATED_BODY()
	
public:
	// Define the ContentTypeId for this Type
	UFUNCTION()
	void GetContentType_UBeamballSkinItem(FString& Result){Result = TEXT("itemskin");};
	
	// Define a SoftObjectPath for the skin item data Asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UBeamBallSkinDataAsset> SkinData;
};
