#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionDeleteRequestBody.h"

#include "StatClientSubscriptionDeleteRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatClientSubscriptionDeleteRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StatClientSubscriptionDeleteRequestBody To JSON String")
	static FString StatClientSubscriptionDeleteRequestBodyToJsonString(const UStatClientSubscriptionDeleteRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StatClientSubscriptionDeleteRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bDeleteAll, Outer", NativeMakeFunc))
	static UStatClientSubscriptionDeleteRequestBody* Make(FBeamGamerTag TargetGamerTag, TArray<FString> Keys, FOptionalBool bDeleteAll, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StatClientSubscriptionDeleteRequestBody", meta=(NativeBreakFunc))
	static void Break(const UStatClientSubscriptionDeleteRequestBody* Serializable, FBeamGamerTag& TargetGamerTag, TArray<FString>& Keys, FOptionalBool& bDeleteAll);
};