
#pragma once

#include "CoreMinimal.h"
#include "TournamentQueryResponse.h"

#include "TournamentQueryResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTournamentQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TournamentQueryResponse To JSON String")
	static FString TournamentQueryResponseToJsonString(const UTournamentQueryResponse* Serializable, const bool Pretty);		
};