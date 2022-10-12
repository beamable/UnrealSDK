
#pragma once

#include "CoreMinimal.h"
#include "ObjectRequestBody.h"

#include "ObjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ObjectRequestBody To JSON String")
	static FString ObjectRequestBodyToJsonString(const UObjectRequestBody* Serializable, const bool Pretty);		
};