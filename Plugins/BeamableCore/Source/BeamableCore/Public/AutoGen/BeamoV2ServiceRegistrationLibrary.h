#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistration.h"

#include "BeamoV2ServiceRegistrationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceRegistrationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceRegistration To JSON String")
	static FString BeamoV2ServiceRegistrationToJsonString(const UBeamoV2ServiceRegistration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceRegistration", meta=(DefaultToSelf="Outer", AdvancedDisplay="bTrafficFilterEnabled, InstanceCount, ServiceName, Cid, Pid, BeamoName, RoutingKey, StartedById, Federation, Outer", NativeMakeFunc))
	static UBeamoV2ServiceRegistration* Make(FOptionalBool bTrafficFilterEnabled, FOptionalInt32 InstanceCount, FOptionalString ServiceName, FOptionalString Cid, FOptionalString Pid, FOptionalString BeamoName, FOptionalString RoutingKey, FOptionalInt64 StartedById, FOptionalArrayOfBeamoV2SupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceRegistration", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceRegistration* Serializable, FOptionalBool& bTrafficFilterEnabled, FOptionalInt32& InstanceCount, FOptionalString& ServiceName, FOptionalString& Cid, FOptionalString& Pid, FOptionalString& BeamoName, FOptionalString& RoutingKey, FOptionalInt64& StartedById, FOptionalArrayOfBeamoV2SupportedFederation& Federation);
};