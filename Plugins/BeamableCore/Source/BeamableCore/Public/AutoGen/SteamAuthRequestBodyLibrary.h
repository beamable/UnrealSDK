
#pragma once

#include "CoreMinimal.h"
#include "SteamAuthRequestBody.h"

#include "SteamAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USteamAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SteamAuthRequestBody To JSON String")
	static FString SteamAuthRequestBodyToJsonString(const USteamAuthRequestBody* Serializable, const bool Pretty);		
};