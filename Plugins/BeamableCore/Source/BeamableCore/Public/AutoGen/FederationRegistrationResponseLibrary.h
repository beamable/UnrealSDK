#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FederationRegistrationResponse.h"

#include "FederationRegistrationResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFederationRegistrationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="FederationRegistrationResponse To JSON String")
	static FString FederationRegistrationResponseToJsonString(const UFederationRegistrationResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make FederationRegistrationResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Registrations, Outer", NativeMakeFunc))
	static UFederationRegistrationResponse* Make(FOptionalArrayOfFederationRegistration Registrations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break FederationRegistrationResponse", meta=(NativeBreakFunc))
	static void Break(const UFederationRegistrationResponse* Serializable, FOptionalArrayOfFederationRegistration& Registrations);
};