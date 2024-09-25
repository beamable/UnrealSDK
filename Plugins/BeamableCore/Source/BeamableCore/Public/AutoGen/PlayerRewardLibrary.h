#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/PlayerReward.h"

#include "PlayerRewardLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PlayerReward To JSON String")
	static FString PlayerRewardToJsonString(const UPlayerReward* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PlayerReward", meta=(DefaultToSelf="Outer", AdvancedDisplay="bApplyVipBonus, Description, ChangeCurrencies, CallWebhooks, AddItems, Outer", NativeMakeFunc))
	static UPlayerReward* Make(TArray<UItemCreateRequestBody*> AddItemRequests, TMap<FString, FString> AddCurrencyMap, FOptionalBool bApplyVipBonus, FOptionalString Description, FOptionalArrayOfCurrencyChangeReward ChangeCurrencies, FOptionalArrayOfWebhookReward CallWebhooks, FOptionalArrayOfNewItemReward AddItems, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PlayerReward", meta=(NativeBreakFunc))
	static void Break(const UPlayerReward* Serializable, TArray<UItemCreateRequestBody*>& AddItemRequests, TMap<FString, FString>& AddCurrencyMap, FOptionalBool& bApplyVipBonus, FOptionalString& Description, FOptionalArrayOfCurrencyChangeReward& ChangeCurrencies, FOptionalArrayOfWebhookReward& CallWebhooks, FOptionalArrayOfNewItemReward& AddItems);
};