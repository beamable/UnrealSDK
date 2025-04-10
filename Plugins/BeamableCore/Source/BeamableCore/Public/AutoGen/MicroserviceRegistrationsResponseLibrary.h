#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsResponse.h"

#include "MicroserviceRegistrationsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMicroserviceRegistrationsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="MicroserviceRegistrationsResponse To JSON String")
	static FString MicroserviceRegistrationsResponseToJsonString(const UMicroserviceRegistrationsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make MicroserviceRegistrationsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMicroserviceRegistrationsResponse* Make(TArray<UMicroserviceRegistrations*> Registrations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break MicroserviceRegistrationsResponse", meta=(NativeBreakFunc))
	static void Break(const UMicroserviceRegistrationsResponse* Serializable, TArray<UMicroserviceRegistrations*>& Registrations);
};