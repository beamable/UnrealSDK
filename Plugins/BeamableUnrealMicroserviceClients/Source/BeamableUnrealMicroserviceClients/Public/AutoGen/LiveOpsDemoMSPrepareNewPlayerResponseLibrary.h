#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSPrepareNewPlayerResponse.h"

#include "LiveOpsDemoMSPrepareNewPlayerResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSPrepareNewPlayerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Json", DisplayName="LiveOpsDemoMSPrepareNewPlayerResponse To JSON String")
	static FString LiveOpsDemoMSPrepareNewPlayerResponseToJsonString(const ULiveOpsDemoMSPrepareNewPlayerResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make LiveOpsDemoMSPrepareNewPlayerResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMSPrepareNewPlayerResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Break LiveOpsDemoMSPrepareNewPlayerResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMSPrepareNewPlayerResponse* Serializable, bool& bValue);
};