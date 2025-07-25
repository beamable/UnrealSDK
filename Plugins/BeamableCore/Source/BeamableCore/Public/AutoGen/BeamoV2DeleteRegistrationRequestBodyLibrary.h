#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2DeleteRegistrationRequestBody.h"

#include "BeamoV2DeleteRegistrationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2DeleteRegistrationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2DeleteRegistrationRequestBody To JSON String")
	static FString BeamoV2DeleteRegistrationRequestBodyToJsonString(const UBeamoV2DeleteRegistrationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2DeleteRegistrationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="RoutingKey, Outer", NativeMakeFunc))
	static UBeamoV2DeleteRegistrationRequestBody* Make(FOptionalString RoutingKey, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2DeleteRegistrationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2DeleteRegistrationRequestBody* Serializable, FOptionalString& RoutingKey);
};