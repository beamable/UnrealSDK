#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsResponse.h"

#include "MicroserviceRegistrationsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMicroserviceRegistrationsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MicroserviceRegistrationsResponse To JSON String")
	static FString MicroserviceRegistrationsResponseToJsonString(const UMicroserviceRegistrationsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MicroserviceRegistrationsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMicroserviceRegistrationsResponse* Make(TArray<UMicroserviceRegistrations*> Registrations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MicroserviceRegistrationsResponse", meta=(NativeBreakFunc))
	static void Break(const UMicroserviceRegistrationsResponse* Serializable, TArray<UMicroserviceRegistrations*>& Registrations);
};