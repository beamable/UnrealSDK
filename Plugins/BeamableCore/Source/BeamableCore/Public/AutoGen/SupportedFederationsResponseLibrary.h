#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SupportedFederationsResponse.h"

#include "SupportedFederationsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USupportedFederationsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SupportedFederationsResponse To JSON String")
	static FString SupportedFederationsResponseToJsonString(const USupportedFederationsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SupportedFederationsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USupportedFederationsResponse* Make(TArray<USupportedFederationRegistration*> Registrations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SupportedFederationsResponse", meta=(NativeBreakFunc))
	static void Break(const USupportedFederationsResponse* Serializable, TArray<USupportedFederationRegistration*>& Registrations);
};