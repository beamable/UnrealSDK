#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationQuery.h"

#include "BeamoV2ServiceRegistrationQueryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceRegistrationQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceRegistrationQuery To JSON String")
	static FString BeamoV2ServiceRegistrationQueryToJsonString(const UBeamoV2ServiceRegistrationQuery* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceRegistrationQuery", meta=(DefaultToSelf="Outer", AdvancedDisplay="bLocalOnly, ServiceName, RoutingKey, Federation, Outer", NativeMakeFunc))
	static UBeamoV2ServiceRegistrationQuery* Make(FOptionalBool bLocalOnly, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalBeamoV2SupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceRegistrationQuery", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceRegistrationQuery* Serializable, FOptionalBool& bLocalOnly, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalBeamoV2SupportedFederation& Federation);
};