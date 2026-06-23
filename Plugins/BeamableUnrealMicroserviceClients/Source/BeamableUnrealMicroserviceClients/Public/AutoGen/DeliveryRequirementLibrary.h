#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliveryRequirement.h"

#include "DeliveryRequirementLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDeliveryRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="DeliveryRequirement To JSON String")
	static FString DeliveryRequirementToJsonString(const UDeliveryRequirement* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make DeliveryRequirement", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeliveryRequirement* Make(FString PropertyName, FString Comparison, int32 Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break DeliveryRequirement", meta=(NativeBreakFunc))
	static void Break(const UDeliveryRequirement* Serializable, FString& PropertyName, FString& Comparison, int32& Value);
};