
#pragma once

#include "CoreMinimal.h"
#include "TournamentQueryRequestBody.h"

#include "TournamentQueryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTournamentQueryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TournamentQueryRequestBody To JSON String")
	static FString TournamentQueryRequestBodyToJsonString(const UTournamentQueryRequestBody* Serializable, const bool Pretty);		
};