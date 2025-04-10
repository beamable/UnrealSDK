#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSIncrementStatResponse.h"

#include "LiveOpsDemoMSIncrementStatResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSIncrementStatResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="LiveOpsDemoMSIncrementStatResponse To JSON String")
	static FString LiveOpsDemoMSIncrementStatResponseToJsonString(const ULiveOpsDemoMSIncrementStatResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|2 - Backend", DisplayName="Make LiveOpsDemoMSIncrementStatResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMSIncrementStatResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|2 - Backend", DisplayName="Break LiveOpsDemoMSIncrementStatResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMSIncrementStatResponse* Serializable, bool& bValue);
};