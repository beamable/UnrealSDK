#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetDeliveryOrdersResult.h"

#include "GetDeliveryOrdersResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGetDeliveryOrdersResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="GetDeliveryOrdersResult To JSON String")
	static FString GetDeliveryOrdersResultToJsonString(const UGetDeliveryOrdersResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make GetDeliveryOrdersResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetDeliveryOrdersResult* Make(bool bSuccess, FString Message, TArray<UDeliveryOrderInfo*> Orders, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break GetDeliveryOrdersResult", meta=(NativeBreakFunc))
	static void Break(const UGetDeliveryOrdersResult* Serializable, bool& bSuccess, FString& Message, TArray<UDeliveryOrderInfo*>& Orders);
};