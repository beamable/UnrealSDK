#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationRequestBody.h"

#include "BeamoV2ServiceRegistrationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceRegistrationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceRegistrationRequestBody To JSON String")
	static FString BeamoV2ServiceRegistrationRequestBodyToJsonString(const UBeamoV2ServiceRegistrationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceRegistrationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="RoutingKey, bTrafficFilterEnabled, Federation, Outer", NativeMakeFunc))
	static UBeamoV2ServiceRegistrationRequestBody* Make(FOptionalString RoutingKey, FOptionalBool bTrafficFilterEnabled, FOptionalArrayOfBeamoV2SupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceRegistrationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceRegistrationRequestBody* Serializable, FOptionalString& RoutingKey, FOptionalBool& bTrafficFilterEnabled, FOptionalArrayOfBeamoV2SupportedFederation& Federation);
};