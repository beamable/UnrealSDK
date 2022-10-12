
#pragma once

#include "CoreMinimal.h"
#include "ServiceStatus.h"

#include "ServiceStatusLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServiceStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServiceStatus To JSON String")
	static FString ServiceStatusToJsonString(const UServiceStatus* Serializable, const bool Pretty);		
};