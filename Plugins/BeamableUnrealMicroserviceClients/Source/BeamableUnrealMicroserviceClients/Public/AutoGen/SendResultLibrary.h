#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendResult.h"

#include "SendResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API USendResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="SendResult To JSON String")
	static FString SendResultToJsonString(const USendResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make SendResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendResult* Make(int32 Attempted, int32 Succeeded, int32 Failed, bool bSuccess, TArray<FString> Messages, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break SendResult", meta=(NativeBreakFunc))
	static void Break(const USendResult* Serializable, int32& Attempted, int32& Succeeded, int32& Failed, bool& bSuccess, TArray<FString>& Messages);
};