
#pragma once

#include "CoreMinimal.h"
#include "GetManifestResponse.h"

#include "GetManifestResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetManifestResponse To JSON String")
	static FString GetManifestResponseToJsonString(const UGetManifestResponse* Serializable, const bool Pretty);		
};