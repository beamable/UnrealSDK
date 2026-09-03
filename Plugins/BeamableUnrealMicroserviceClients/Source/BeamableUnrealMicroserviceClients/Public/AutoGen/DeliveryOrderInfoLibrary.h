#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliveryOrderInfo.h"

#include "DeliveryOrderInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDeliveryOrderInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="DeliveryOrderInfo To JSON String")
	static FString DeliveryOrderInfoToJsonString(const UDeliveryOrderInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make DeliveryOrderInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeliveryOrderInfo* Make(FString OrderId, FString DisplayName, FString RequiredItemContentId, FString RewardCurrencyId, int32 RewardAmount, TArray<UDeliveryRequirement*> Requirements, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break DeliveryOrderInfo", meta=(NativeBreakFunc))
	static void Break(const UDeliveryOrderInfo* Serializable, FString& OrderId, FString& DisplayName, FString& RequiredItemContentId, FString& RewardCurrencyId, int32& RewardAmount, TArray<UDeliveryRequirement*>& Requirements);
};