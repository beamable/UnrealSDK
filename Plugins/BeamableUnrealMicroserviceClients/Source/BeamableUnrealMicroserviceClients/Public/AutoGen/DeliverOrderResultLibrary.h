#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliverOrderResult.h"

#include "DeliverOrderResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDeliverOrderResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="DeliverOrderResult To JSON String")
	static FString DeliverOrderResultToJsonString(const UDeliverOrderResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make DeliverOrderResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeliverOrderResult* Make(FString OrderId, FString RewardCurrencyId, int32 RewardAmount, FString Message, bool bSuccess, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break DeliverOrderResult", meta=(NativeBreakFunc))
	static void Break(const UDeliverOrderResult* Serializable, FString& OrderId, FString& RewardCurrencyId, int32& RewardAmount, FString& Message, bool& bSuccess);
};