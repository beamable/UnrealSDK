
#pragma once

#include "CoreMinimal.h"
#include "GetCurrentManifestRequestBody.h"

#include "GetCurrentManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCurrentManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetCurrentManifestRequestBody To JSON String")
	static FString GetCurrentManifestRequestBodyToJsonString(const UGetCurrentManifestRequestBody* Serializable, const bool Pretty);		
};