
#pragma once

#include "CoreMinimal.h"
#include "GetStandingsRequestBody.h"

#include "GetStandingsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStandingsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetStandingsRequestBody To JSON String")
	static FString GetStandingsRequestBodyToJsonString(const UGetStandingsRequestBody* Serializable, const bool Pretty);		
};