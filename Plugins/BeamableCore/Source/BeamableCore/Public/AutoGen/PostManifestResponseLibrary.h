
#pragma once

#include "CoreMinimal.h"
#include "PostManifestResponse.h"

#include "PostManifestResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPostManifestResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PostManifestResponse To JSON String")
	static FString PostManifestResponseToJsonString(const UPostManifestResponse* Serializable, const bool Pretty);		
};