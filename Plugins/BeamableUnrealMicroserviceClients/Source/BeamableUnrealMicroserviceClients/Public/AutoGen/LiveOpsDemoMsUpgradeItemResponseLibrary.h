#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSUpgradeItemResponse.h"

#include "LiveOpsDemoMSUpgradeItemResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSUpgradeItemResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LiveOpsDemoMSUpgradeItemResponse To JSON String")
	static FString LiveOpsDemoMSUpgradeItemResponseToJsonString(const ULiveOpsDemoMSUpgradeItemResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LiveOpsDemoMSUpgradeItemResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMSUpgradeItemResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LiveOpsDemoMSUpgradeItemResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMSUpgradeItemResponse* Serializable, bool& bValue);
};