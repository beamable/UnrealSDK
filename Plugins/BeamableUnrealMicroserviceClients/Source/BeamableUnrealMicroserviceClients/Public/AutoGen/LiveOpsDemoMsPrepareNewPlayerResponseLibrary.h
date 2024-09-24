#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsPrepareNewPlayerResponse.h"

#include "LiveOpsDemoMsPrepareNewPlayerResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMsPrepareNewPlayerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LiveOpsDemoMsPrepareNewPlayerResponse To JSON String")
	static FString LiveOpsDemoMsPrepareNewPlayerResponseToJsonString(const ULiveOpsDemoMsPrepareNewPlayerResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LiveOpsDemoMsPrepareNewPlayerResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMsPrepareNewPlayerResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LiveOpsDemoMsPrepareNewPlayerResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMsPrepareNewPlayerResponse* Serializable, bool& bValue);
};