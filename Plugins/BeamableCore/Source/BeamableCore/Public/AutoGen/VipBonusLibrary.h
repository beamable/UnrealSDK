
#pragma once

#include "CoreMinimal.h"
#include "VipBonus.h"

#include "VipBonusLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UVipBonusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize VipBonus To JSON String")
	static FString VipBonusToJsonString(const UVipBonus* Serializable, const bool Pretty);		
};