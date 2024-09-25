#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/SubscriptionVerificationResponse.h"

#include "SubscriptionVerificationResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USubscriptionVerificationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SubscriptionVerificationResponse To JSON String")
	static FString SubscriptionVerificationResponseToJsonString(const USubscriptionVerificationResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SubscriptionVerificationResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USubscriptionVerificationResponse* Make(FString HubChallenge, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SubscriptionVerificationResponse", meta=(NativeBreakFunc))
	static void Break(const USubscriptionVerificationResponse* Serializable, FString& HubChallenge);
};