#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionData.h"

#include "StatClientSubscriptionDataLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatClientSubscriptionDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StatClientSubscriptionData To JSON String")
	static FString StatClientSubscriptionDataToJsonString(const UStatClientSubscriptionData* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StatClientSubscriptionData", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatClientSubscriptionData* Make(int64 TargetGamerTag, TArray<FString> Keys, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StatClientSubscriptionData", meta=(NativeBreakFunc))
	static void Break(const UStatClientSubscriptionData* Serializable, int64& TargetGamerTag, TArray<FString>& Keys);
};