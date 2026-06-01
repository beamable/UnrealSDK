// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentObject.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"

#include "BeamDeliveryOrderPoolContent.generated.h"

/**
 * BeamDeliveryOrderPoolContent configures the delivery order system for a realm.
 * Create a single instance with ID "delivery_order_config.default" and publish it.
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamDeliveryOrderPoolContent : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamDeliveryOrderPoolContent(FString& Result) { Result = TEXT("delivery_order_config"); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	int32 MaxActiveOrders = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	TArray<FBeamContentId> OrderPool;
};
