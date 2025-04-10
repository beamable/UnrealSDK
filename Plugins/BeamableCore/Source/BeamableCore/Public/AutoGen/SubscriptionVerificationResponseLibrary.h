#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SubscriptionVerificationResponse.h"

#include "SubscriptionVerificationResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USubscriptionVerificationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="SubscriptionVerificationResponse To JSON String")
	static FString SubscriptionVerificationResponseToJsonString(const USubscriptionVerificationResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make SubscriptionVerificationResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USubscriptionVerificationResponse* Make(FString HubChallenge, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break SubscriptionVerificationResponse", meta=(NativeBreakFunc))
	static void Break(const USubscriptionVerificationResponse* Serializable, FString& HubChallenge);
};