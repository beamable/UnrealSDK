
#pragma once

#include "CoreMinimal.h"
#include "MatchUpdate.h"

#include "MatchUpdateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMatchUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MatchUpdate To JSON String")
	static FString MatchUpdateToJsonString(const UMatchUpdate* Serializable, const bool Pretty);		
};