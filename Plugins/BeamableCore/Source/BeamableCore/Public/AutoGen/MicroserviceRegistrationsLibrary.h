#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrations.h"

#include "MicroserviceRegistrationsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMicroserviceRegistrationsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MicroserviceRegistrations To JSON String")
	static FString MicroserviceRegistrationsToJsonString(const UMicroserviceRegistrations* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MicroserviceRegistrations", meta=(DefaultToSelf="Outer", AdvancedDisplay="bTrafficFilterEnabled, RoutingKey, StartedById, BeamoName, Federation, Outer", NativeMakeFunc))
	static UMicroserviceRegistrations* Make(FString ServiceName, FString Cid, FString Pid, int32 InstanceCount, FOptionalBool bTrafficFilterEnabled, FOptionalString RoutingKey, FOptionalInt64 StartedById, FOptionalString BeamoName, FOptionalArrayOfSupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MicroserviceRegistrations", meta=(NativeBreakFunc))
	static void Break(const UMicroserviceRegistrations* Serializable, FString& ServiceName, FString& Cid, FString& Pid, int32& InstanceCount, FOptionalBool& bTrafficFilterEnabled, FOptionalString& RoutingKey, FOptionalInt64& StartedById, FOptionalString& BeamoName, FOptionalArrayOfSupportedFederation& Federation);
};