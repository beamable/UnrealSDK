// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamItemContent.h"
#include "SecondItemContent.generated.h"

/**
 * 
 */
UCLASS()
class BEAMPROJ_BEAMBALL_API USecondItemContent : public UBeamItemContent
{
	GENERATED_BODY()
public:
	// Define the ContentTypeId for this Type
	UFUNCTION()
	void GetContentType_USecondItemContent(FString& Result){Result = TEXT("secondcontent");};
};
