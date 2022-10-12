
#pragma once

#include "CoreMinimal.h"
#include "SteamOrderInfoItem.h"

#include "SteamOrderInfoItemLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USteamOrderInfoItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SteamOrderInfoItem To JSON String")
	static FString SteamOrderInfoItemToJsonString(const USteamOrderInfoItem* Serializable, const bool Pretty);		
};