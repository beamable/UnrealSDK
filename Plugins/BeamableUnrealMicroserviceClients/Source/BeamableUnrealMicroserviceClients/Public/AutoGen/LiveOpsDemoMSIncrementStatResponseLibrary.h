#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSIncrementStatResponse.h"

#include "LiveOpsDemoMSIncrementStatResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSIncrementStatResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LiveOpsDemoMSIncrementStatResponse To JSON String")
	static FString LiveOpsDemoMSIncrementStatResponseToJsonString(const ULiveOpsDemoMSIncrementStatResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LiveOpsDemoMSIncrementStatResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMSIncrementStatResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LiveOpsDemoMSIncrementStatResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMSIncrementStatResponse* Serializable, bool& bValue);
};