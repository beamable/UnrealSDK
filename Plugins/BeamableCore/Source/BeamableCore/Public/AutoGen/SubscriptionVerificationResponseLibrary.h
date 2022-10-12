
#pragma once

#include "CoreMinimal.h"
#include "SubscriptionVerificationResponse.h"

#include "SubscriptionVerificationResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USubscriptionVerificationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SubscriptionVerificationResponse To JSON String")
	static FString SubscriptionVerificationResponseToJsonString(const USubscriptionVerificationResponse* Serializable, const bool Pretty);		
};