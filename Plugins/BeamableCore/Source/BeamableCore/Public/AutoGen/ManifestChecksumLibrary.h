
#pragma once

#include "CoreMinimal.h"
#include "ManifestChecksum.h"

#include "ManifestChecksumLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UManifestChecksumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ManifestChecksum To JSON String")
	static FString ManifestChecksumToJsonString(const UManifestChecksum* Serializable, const bool Pretty);		
};