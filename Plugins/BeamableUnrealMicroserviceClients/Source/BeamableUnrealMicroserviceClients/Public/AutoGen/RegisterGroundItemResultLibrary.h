#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterGroundItemResult.h"

#include "RegisterGroundItemResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API URegisterGroundItemResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="RegisterGroundItemResult To JSON String")
	static FString RegisterGroundItemResultToJsonString(const URegisterGroundItemResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make RegisterGroundItemResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URegisterGroundItemResult* Make(bool bSuccess, FString Message, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break RegisterGroundItemResult", meta=(NativeBreakFunc))
	static void Break(const URegisterGroundItemResult* Serializable, bool& bSuccess, FString& Message);
};