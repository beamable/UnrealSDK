
#pragma once

#include "CoreMinimal.h"
#include "CommonResponse.h"

#include "CommonResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCommonResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CommonResponse To JSON String")
	static FString CommonResponseToJsonString(const UCommonResponse* Serializable, const bool Pretty);		
};