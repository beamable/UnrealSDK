#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SupportedFederationsResponse.h"

#include "SupportedFederationsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USupportedFederationsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|4 - Json", DisplayName="SupportedFederationsResponse To JSON String")
	static FString SupportedFederationsResponseToJsonString(const USupportedFederationsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|3 - Backend", DisplayName="Make SupportedFederationsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USupportedFederationsResponse* Make(TArray<USupportedFederationRegistration*> Registrations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|3 - Backend", DisplayName="Break SupportedFederationsResponse", meta=(NativeBreakFunc))
	static void Break(const USupportedFederationsResponse* Serializable, TArray<USupportedFederationRegistration*>& Registrations);
};