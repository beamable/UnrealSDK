
#pragma once

#include "CoreMinimal.h"
#include "MailRewards.h"

#include "MailRewardsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMailRewardsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MailRewards To JSON String")
	static FString MailRewardsToJsonString(const UMailRewards* Serializable, const bool Pretty);		
};