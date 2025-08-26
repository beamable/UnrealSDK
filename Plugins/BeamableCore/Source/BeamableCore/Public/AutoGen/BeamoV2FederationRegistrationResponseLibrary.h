#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2FederationRegistrationResponse.h"

#include "BeamoV2FederationRegistrationResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2FederationRegistrationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2FederationRegistrationResponse To JSON String")
	static FString BeamoV2FederationRegistrationResponseToJsonString(const UBeamoV2FederationRegistrationResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2FederationRegistrationResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Registrations, Outer", NativeMakeFunc))
	static UBeamoV2FederationRegistrationResponse* Make(FOptionalArrayOfBeamoV2FederationRegistration Registrations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2FederationRegistrationResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2FederationRegistrationResponse* Serializable, FOptionalArrayOfBeamoV2FederationRegistration& Registrations);
};