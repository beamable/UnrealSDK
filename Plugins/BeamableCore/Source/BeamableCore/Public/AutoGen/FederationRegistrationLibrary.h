#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FederationRegistration.h"

#include "FederationRegistrationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFederationRegistrationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="FederationRegistration To JSON String")
	static FString FederationRegistrationToJsonString(const UFederationRegistration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make FederationRegistration", meta=(DefaultToSelf="Outer", AdvancedDisplay="bTrafficFilterEnabled, ServiceName, RoutingKey, Ttl, Federation, Outer", NativeMakeFunc))
	static UFederationRegistration* Make(FOptionalBool bTrafficFilterEnabled, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalDateTime Ttl, FOptionalArrayOfSupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break FederationRegistration", meta=(NativeBreakFunc))
	static void Break(const UFederationRegistration* Serializable, FOptionalBool& bTrafficFilterEnabled, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalDateTime& Ttl, FOptionalArrayOfSupportedFederation& Federation);
};