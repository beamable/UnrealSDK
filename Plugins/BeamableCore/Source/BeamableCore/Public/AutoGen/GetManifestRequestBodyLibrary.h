
#pragma once

#include "CoreMinimal.h"
#include "GetManifestRequestBody.h"

#include "GetManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetManifestRequestBody To JSON String")
	static FString GetManifestRequestBodyToJsonString(const UGetManifestRequestBody* Serializable, const bool Pretty);		
};