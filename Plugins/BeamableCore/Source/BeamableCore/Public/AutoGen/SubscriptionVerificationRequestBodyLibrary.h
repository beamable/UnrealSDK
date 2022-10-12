
#pragma once

#include "CoreMinimal.h"
#include "SubscriptionVerificationRequestBody.h"

#include "SubscriptionVerificationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USubscriptionVerificationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SubscriptionVerificationRequestBody To JSON String")
	static FString SubscriptionVerificationRequestBodyToJsonString(const USubscriptionVerificationRequestBody* Serializable, const bool Pretty);		
};