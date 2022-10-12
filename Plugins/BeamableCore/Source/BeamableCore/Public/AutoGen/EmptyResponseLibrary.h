
#pragma once

#include "CoreMinimal.h"
#include "EmptyResponse.h"

#include "EmptyResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEmptyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EmptyResponse To JSON String")
	static FString EmptyResponseToJsonString(const UEmptyResponse* Serializable, const bool Pretty);		
};