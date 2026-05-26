#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/FillDeliveryOrdersResult.h"

#include "FillDeliveryOrdersResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UFillDeliveryOrdersResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="FillDeliveryOrdersResult To JSON String")
	static FString FillDeliveryOrdersResultToJsonString(const UFillDeliveryOrdersResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make FillDeliveryOrdersResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFillDeliveryOrdersResult* Make(int32 OrdersAdded, bool bSuccess, int32 TotalOrders, FString Message, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break FillDeliveryOrdersResult", meta=(NativeBreakFunc))
	static void Break(const UFillDeliveryOrdersResult* Serializable, int32& OrdersAdded, bool& bSuccess, int32& TotalOrders, FString& Message);
};