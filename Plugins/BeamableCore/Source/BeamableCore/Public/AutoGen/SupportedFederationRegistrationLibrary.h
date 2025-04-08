#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SupportedFederationRegistration.h"

#include "SupportedFederationRegistrationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USupportedFederationRegistrationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="SupportedFederationRegistration To JSON String")
	static FString SupportedFederationRegistrationToJsonString(const USupportedFederationRegistration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make SupportedFederationRegistration", meta=(DefaultToSelf="Outer", AdvancedDisplay="RoutingKey, Federation, Outer", NativeMakeFunc))
	static USupportedFederationRegistration* Make(bool bTrafficFilterEnabled, FString ServiceName, FOptionalString RoutingKey, FOptionalArrayOfSupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break SupportedFederationRegistration", meta=(NativeBreakFunc))
	static void Break(const USupportedFederationRegistration* Serializable, bool& bTrafficFilterEnabled, FString& ServiceName, FOptionalString& RoutingKey, FOptionalArrayOfSupportedFederation& Federation);
};