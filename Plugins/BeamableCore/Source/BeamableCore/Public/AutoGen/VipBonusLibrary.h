#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/VipBonus.h"

#include "VipBonusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UVipBonusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - VipBonus To JSON String")
	static FString VipBonusToJsonString(const UVipBonus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make VipBonus", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UVipBonus* Make(FString Currency, double Multiplier, int32 RoundToNearest, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break VipBonus", meta=(NativeBreakFunc))
	static void Break(const UVipBonus* Serializable, FString& Currency, double& Multiplier, int32& RoundToNearest);
};