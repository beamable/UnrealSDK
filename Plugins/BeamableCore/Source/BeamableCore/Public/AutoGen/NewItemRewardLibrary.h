#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/NewItemReward.h"

#include "NewItemRewardLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UNewItemRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - NewItemReward To JSON String")
	static FString NewItemRewardToJsonString(const UNewItemReward* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make NewItemReward", meta=(DefaultToSelf="Outer", AdvancedDisplay="Properties, Outer", NativeMakeFunc))
	static UNewItemReward* Make(FString Symbol, FOptionalMapOfString Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break NewItemReward", meta=(NativeBreakFunc))
	static void Break(const UNewItemReward* Serializable, FString& Symbol, FOptionalMapOfString& Properties);
};