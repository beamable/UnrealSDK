#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceRegistrationResponse.h"

#include "ServiceRegistrationResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceRegistrationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceRegistrationResponse To JSON String")
	static FString ServiceRegistrationResponseToJsonString(const UServiceRegistrationResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceRegistrationResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Registrations, Outer", NativeMakeFunc))
	static UServiceRegistrationResponse* Make(FOptionalArrayOfServiceRegistration Registrations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceRegistrationResponse", meta=(NativeBreakFunc))
	static void Break(const UServiceRegistrationResponse* Serializable, FOptionalArrayOfServiceRegistration& Registrations);
};