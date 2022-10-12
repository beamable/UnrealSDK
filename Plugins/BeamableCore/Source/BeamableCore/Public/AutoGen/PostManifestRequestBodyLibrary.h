
#pragma once

#include "CoreMinimal.h"
#include "PostManifestRequestBody.h"

#include "PostManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPostManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PostManifestRequestBody To JSON String")
	static FString PostManifestRequestBodyToJsonString(const UPostManifestRequestBody* Serializable, const bool Pretty);		
};