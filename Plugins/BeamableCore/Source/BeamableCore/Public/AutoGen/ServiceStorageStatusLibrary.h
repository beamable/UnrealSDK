
#pragma once

#include "CoreMinimal.h"
#include "ServiceStorageStatus.h"

#include "ServiceStorageStatusLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServiceStorageStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServiceStorageStatus To JSON String")
	static FString ServiceStorageStatusToJsonString(const UServiceStorageStatus* Serializable, const bool Pretty);		
};