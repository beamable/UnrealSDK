#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceRegistration.h"

#include "ServiceRegistrationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceRegistrationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceRegistration To JSON String")
	static FString ServiceRegistrationToJsonString(const UServiceRegistration* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceRegistration", meta=(DefaultToSelf="Outer", AdvancedDisplay="bTrafficFilterEnabled, InstanceCount, ServiceName, Cid, Pid, BeamoName, RoutingKey, StartedById, Federation, Outer", NativeMakeFunc))
	static UServiceRegistration* Make(FOptionalBool bTrafficFilterEnabled, FOptionalInt32 InstanceCount, FOptionalString ServiceName, FOptionalString Cid, FOptionalString Pid, FOptionalString BeamoName, FOptionalString RoutingKey, FOptionalInt64 StartedById, FOptionalArrayOfSupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceRegistration", meta=(NativeBreakFunc))
	static void Break(const UServiceRegistration* Serializable, FOptionalBool& bTrafficFilterEnabled, FOptionalInt32& InstanceCount, FOptionalString& ServiceName, FOptionalString& Cid, FOptionalString& Pid, FOptionalString& BeamoName, FOptionalString& RoutingKey, FOptionalInt64& StartedById, FOptionalArrayOfSupportedFederation& Federation);
};