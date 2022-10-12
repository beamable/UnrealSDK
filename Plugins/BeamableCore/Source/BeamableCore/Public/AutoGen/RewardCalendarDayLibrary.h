
#pragma once

#include "CoreMinimal.h"
#include "RewardCalendarDay.h"

#include "RewardCalendarDayLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URewardCalendarDayLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RewardCalendarDay To JSON String")
	static FString RewardCalendarDayToJsonString(const URewardCalendarDay* Serializable, const bool Pretty);		
};