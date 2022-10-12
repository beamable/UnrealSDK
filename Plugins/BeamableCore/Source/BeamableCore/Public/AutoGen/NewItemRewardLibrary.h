
#pragma once

#include "CoreMinimal.h"
#include "NewItemReward.h"

#include "NewItemRewardLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UNewItemRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize NewItemReward To JSON String")
	static FString NewItemRewardToJsonString(const UNewItemReward* Serializable, const bool Pretty);		
};