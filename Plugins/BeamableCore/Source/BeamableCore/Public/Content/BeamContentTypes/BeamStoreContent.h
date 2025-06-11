// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Content/BeamContentObject.h"
#include "BeamStoreContent.generated.h"

/**
 * This type defines a %Beamable %ContentObject subclass for the %CommerceService and Store feature.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamStoreContent : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamStoreContent(FString& Result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString title = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BeamContentTypeFilter="listing", BeamContentTypeFilterMode="tree"))
	TArray<FBeamContentLink> listings = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalBool showInactiveListings = {};
	/// The default value is 20. If you need to show more than 20 listings at a time, change this field.
	/// This is mostly so that you can reduce the size of payloads for store views of this type.	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionalInt32 activeListingLimit = {};
	
};

DEFINE_CONTENT_TYPE_NAME(UBeamStoreContent, "stores")
