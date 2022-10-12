
#pragma once

#include "CoreMinimal.h"
#include "GetManifestsResponse.h"

#include "GetManifestsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetManifestsResponse To JSON String")
	static FString GetManifestsResponseToJsonString(const UGetManifestsResponse* Serializable, const bool Pretty);		
};