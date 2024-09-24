#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsUpgradeItemResponse.h"

#include "LiveOpsDemoMsUpgradeItemResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMsUpgradeItemResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LiveOpsDemoMsUpgradeItemResponse To JSON String")
	static FString LiveOpsDemoMsUpgradeItemResponseToJsonString(const ULiveOpsDemoMsUpgradeItemResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LiveOpsDemoMsUpgradeItemResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMsUpgradeItemResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LiveOpsDemoMsUpgradeItemResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMsUpgradeItemResponse* Serializable, bool& bValue);
};