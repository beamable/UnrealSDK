// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentObject.h"
#include "Farming/FarmTypes.h"

#include "BeamDeliveryOrderContent.generated.h"

/**
 * BeamDeliveryOrderContent represents a single delivery order template in the Beamable content system.
 * Create content with ID pattern "delivery_order.<name>" and publish to your realm.
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamDeliveryOrderContent : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamDeliveryOrderContent(FString& Result) { Result = TEXT("delivery_order"); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	FString RequiredItemContentId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	TArray<FBeamDeliveryRequirement> Requirements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	FString RewardCurrencyId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	int32 RewardAmount = 0;
};
