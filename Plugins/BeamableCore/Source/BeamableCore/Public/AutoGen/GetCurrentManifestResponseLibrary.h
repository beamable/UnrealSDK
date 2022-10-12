
#pragma once

#include "CoreMinimal.h"
#include "GetCurrentManifestResponse.h"

#include "GetCurrentManifestResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCurrentManifestResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetCurrentManifestResponse To JSON String")
	static FString GetCurrentManifestResponseToJsonString(const UGetCurrentManifestResponse* Serializable, const bool Pretty);		
};