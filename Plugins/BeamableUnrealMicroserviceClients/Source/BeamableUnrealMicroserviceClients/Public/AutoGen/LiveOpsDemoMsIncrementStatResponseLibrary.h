#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsIncrementStatResponse.h"

#include "LiveOpsDemoMsIncrementStatResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMsIncrementStatResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LiveOpsDemoMsIncrementStatResponse To JSON String")
	static FString LiveOpsDemoMsIncrementStatResponseToJsonString(const ULiveOpsDemoMsIncrementStatResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LiveOpsDemoMsIncrementStatResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMsIncrementStatResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LiveOpsDemoMsIncrementStatResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMsIncrementStatResponse* Serializable, bool& bValue);
};