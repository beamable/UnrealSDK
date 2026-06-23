#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterResult.h"

#include "RegisterResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API URegisterResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="RegisterResult To JSON String")
	static FString RegisterResultToJsonString(const URegisterResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make RegisterResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URegisterResult* Make(bool bSuccess, int32 DeviceCount, FString Message, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break RegisterResult", meta=(NativeBreakFunc))
	static void Break(const URegisterResult* Serializable, bool& bSuccess, int32& DeviceCount, FString& Message);
};