
#pragma once

#include "CoreMinimal.h"
#include "Period.h"

#include "PeriodLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPeriodLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Period To JSON String")
	static FString PeriodToJsonString(const UPeriod* Serializable, const bool Pretty);		
};