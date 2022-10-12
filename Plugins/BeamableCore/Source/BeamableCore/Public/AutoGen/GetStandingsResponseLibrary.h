
#pragma once

#include "CoreMinimal.h"
#include "GetStandingsResponse.h"

#include "GetStandingsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStandingsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetStandingsResponse To JSON String")
	static FString GetStandingsResponseToJsonString(const UGetStandingsResponse* Serializable, const bool Pretty);		
};