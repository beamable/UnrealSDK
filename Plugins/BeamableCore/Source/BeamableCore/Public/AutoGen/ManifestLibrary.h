
#pragma once

#include "CoreMinimal.h"
#include "Manifest.h"

#include "ManifestLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UManifestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Manifest To JSON String")
	static FString ManifestToJsonString(const UManifest* Serializable, const bool Pretty);		
};