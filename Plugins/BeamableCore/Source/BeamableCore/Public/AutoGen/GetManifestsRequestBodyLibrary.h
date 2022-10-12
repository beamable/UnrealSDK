
#pragma once

#include "CoreMinimal.h"
#include "GetManifestsRequestBody.h"

#include "GetManifestsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetManifestsRequestBody To JSON String")
	static FString GetManifestsRequestBodyToJsonString(const UGetManifestsRequestBody* Serializable, const bool Pretty);		
};