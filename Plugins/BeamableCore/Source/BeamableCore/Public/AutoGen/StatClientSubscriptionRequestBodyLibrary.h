#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionRequestBody.h"

#include "StatClientSubscriptionRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatClientSubscriptionRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StatClientSubscriptionRequestBody To JSON String")
	static FString StatClientSubscriptionRequestBodyToJsonString(const UStatClientSubscriptionRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StatClientSubscriptionRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatClientSubscriptionRequestBody* Make(FBeamGamerTag TargetGamerTag, TArray<FString> Keys, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StatClientSubscriptionRequestBody", meta=(NativeBreakFunc))
	static void Break(const UStatClientSubscriptionRequestBody* Serializable, FBeamGamerTag& TargetGamerTag, TArray<FString>& Keys);
};