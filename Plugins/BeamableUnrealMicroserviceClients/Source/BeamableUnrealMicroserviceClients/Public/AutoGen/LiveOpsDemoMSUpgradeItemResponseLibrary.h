#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSUpgradeItemResponse.h"

#include "LiveOpsDemoMSUpgradeItemResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSUpgradeItemResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Json", DisplayName="LiveOpsDemoMSUpgradeItemResponse To JSON String")
	static FString LiveOpsDemoMSUpgradeItemResponseToJsonString(const ULiveOpsDemoMSUpgradeItemResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make LiveOpsDemoMSUpgradeItemResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULiveOpsDemoMSUpgradeItemResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Break LiveOpsDemoMSUpgradeItemResponse", meta=(NativeBreakFunc))
	static void Break(const ULiveOpsDemoMSUpgradeItemResponse* Serializable, bool& bValue);
};