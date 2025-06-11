// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SecondItemContent.h"
#include "AnotherLayerContent.generated.h"

/**
 * 
 */
UCLASS()
class BEAMPROJ_BEAMBALL_API UAnotherLayerContent : public USecondItemContent
{
	GENERATED_BODY()
public:
	// Define the ContentTypeId for this Type
	UFUNCTION()
	void GetContentType_UAnotherLayerContent(FString& Result){Result = TEXT("anotherlayer");};
};
