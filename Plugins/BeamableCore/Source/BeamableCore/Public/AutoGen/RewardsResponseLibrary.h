
#pragma once

#include "CoreMinimal.h"
#include "RewardsResponse.h"

#include "RewardsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URewardsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RewardsResponse To JSON String")
	static FString RewardsResponseToJsonString(const URewardsResponse* Serializable, const bool Pretty);		
};