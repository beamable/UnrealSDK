#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SetEdgegapLocationRequestArgs.h"

#include "SetEdgegapLocationRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API USetEdgegapLocationRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Json", DisplayName="SetEdgegapLocationRequestArgs To JSON String")
	static FString SetEdgegapLocationRequestArgsToJsonString(const USetEdgegapLocationRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make SetEdgegapLocationRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USetEdgegapLocationRequestArgs* Make(float Latitude, float Longitude, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Break SetEdgegapLocationRequestArgs", meta=(NativeBreakFunc))
	static void Break(const USetEdgegapLocationRequestArgs* Serializable, float& Latitude, float& Longitude);
};