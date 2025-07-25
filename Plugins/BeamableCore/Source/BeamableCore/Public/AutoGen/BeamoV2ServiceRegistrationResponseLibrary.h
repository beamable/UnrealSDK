#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationResponse.h"

#include "BeamoV2ServiceRegistrationResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceRegistrationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceRegistrationResponse To JSON String")
	static FString BeamoV2ServiceRegistrationResponseToJsonString(const UBeamoV2ServiceRegistrationResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceRegistrationResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Registrations, Outer", NativeMakeFunc))
	static UBeamoV2ServiceRegistrationResponse* Make(FOptionalArrayOfBeamoV2ServiceRegistration Registrations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceRegistrationResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceRegistrationResponse* Serializable, FOptionalArrayOfBeamoV2ServiceRegistration& Registrations);
};