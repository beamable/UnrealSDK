#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UnregisterResult.h"

#include "UnregisterResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UUnregisterResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="UnregisterResult To JSON String")
	static FString UnregisterResultToJsonString(const UUnregisterResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make UnregisterResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UUnregisterResult* Make(bool bSuccess, int32 DeviceCount, FString Message, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break UnregisterResult", meta=(NativeBreakFunc))
	static void Break(const UUnregisterResult* Serializable, bool& bSuccess, int32& DeviceCount, FString& Message);
};