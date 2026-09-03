#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliverOrderRequestArgs.h"

#include "DeliverOrderRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDeliverOrderRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="DeliverOrderRequestArgs To JSON String")
	static FString DeliverOrderRequestArgsToJsonString(const UDeliverOrderRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make DeliverOrderRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeliverOrderRequestArgs* Make(FString OrderId, int64 ItemInstanceId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break DeliverOrderRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UDeliverOrderRequestArgs* Serializable, FString& OrderId, int64& ItemInstanceId);
};