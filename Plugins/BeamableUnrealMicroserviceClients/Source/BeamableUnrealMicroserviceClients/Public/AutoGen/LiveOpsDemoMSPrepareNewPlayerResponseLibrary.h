#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSPrepareNewPlayerResponse.h"

#include "LiveOpsDemoMSPrepareNewPlayerResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSPrepareNewPlayerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LiveOpsDemoMSPrepareNewPlayerResponse To JSON String")
	static FString LiveOpsDemoMSPrepareNewPlayerResponseToJsonString(const ULiveOpsDemoMSPrepareNewPlayerResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LiveOpsDemoMSPrepareNewPlayerResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMSPrepareNewPlayerResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LiveOpsDemoMSPrepareNewPlayerResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMSPrepareNewPlayerResponse* Serializable, bool& bValue);
};