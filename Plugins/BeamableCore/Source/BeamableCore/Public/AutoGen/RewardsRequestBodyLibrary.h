
#pragma once

#include "CoreMinimal.h"
#include "RewardsRequestBody.h"

#include "RewardsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URewardsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RewardsRequestBody To JSON String")
	static FString RewardsRequestBodyToJsonString(const URewardsRequestBody* Serializable, const bool Pretty);		
};