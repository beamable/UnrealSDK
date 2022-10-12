
#pragma once

#include "CoreMinimal.h"
#include "TournamentGroupEntry.h"

#include "TournamentGroupEntryLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTournamentGroupEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TournamentGroupEntry To JSON String")
	static FString TournamentGroupEntryToJsonString(const UTournamentGroupEntry* Serializable, const bool Pretty);		
};