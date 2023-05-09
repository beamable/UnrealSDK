#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailRewards.h"

#include "MailRewardsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailRewardsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MailRewards To JSON String")
	static FString MailRewardsToJsonString(const UMailRewards* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MailRewards", meta=(DefaultToSelf="Outer", AdvancedDisplay="bApplyVipBonus, Outer", NativeMakeFunc))
	static UMailRewards* Make(TArray<UCurrencyChange*> Currencies, TArray<UItemCreateRequestBody*> Items, FOptionalBool bApplyVipBonus, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MailRewards", meta=(NativeBreakFunc))
	static void Break(const UMailRewards* Serializable, TArray<UCurrencyChange*>& Currencies, TArray<UItemCreateRequestBody*>& Items, FOptionalBool& bApplyVipBonus);
};