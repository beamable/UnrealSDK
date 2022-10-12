
#pragma once

#include "CoreMinimal.h"
#include "ManifestView.h"

#include "ManifestViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UManifestViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ManifestView To JSON String")
	static FString ManifestViewToJsonString(const UManifestView* Serializable, const bool Pretty);		
};