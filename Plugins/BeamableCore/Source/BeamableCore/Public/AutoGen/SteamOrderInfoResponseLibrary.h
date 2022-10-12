
#pragma once

#include "CoreMinimal.h"
#include "SteamOrderInfoResponse.h"

#include "SteamOrderInfoResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USteamOrderInfoResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SteamOrderInfoResponse To JSON String")
	static FString SteamOrderInfoResponseToJsonString(const USteamOrderInfoResponse* Serializable, const bool Pretty);		
};