#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2FederationRegistration.h"

#include "BeamoV2FederationRegistrationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2FederationRegistrationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2FederationRegistration To JSON String")
	static FString BeamoV2FederationRegistrationToJsonString(const UBeamoV2FederationRegistration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2FederationRegistration", meta=(DefaultToSelf="Outer", AdvancedDisplay="bTrafficFilterEnabled, ServiceName, RoutingKey, Ttl, Federation, Outer", NativeMakeFunc))
	static UBeamoV2FederationRegistration* Make(FOptionalBool bTrafficFilterEnabled, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalDateTime Ttl, FOptionalArrayOfBeamoV2SupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2FederationRegistration", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2FederationRegistration* Serializable, FOptionalBool& bTrafficFilterEnabled, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalDateTime& Ttl, FOptionalArrayOfBeamoV2SupportedFederation& Federation);
};