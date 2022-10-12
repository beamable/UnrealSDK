
#pragma once

#include "CoreMinimal.h"
#include "ServicePlansResponse.h"

#include "ServicePlansResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServicePlansResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServicePlansResponse To JSON String")
	static FString ServicePlansResponseToJsonString(const UServicePlansResponse* Serializable, const bool Pretty);		
};