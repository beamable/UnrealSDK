
#pragma once

#include "CoreMinimal.h"
#include "TournamentEntry.h"

#include "TournamentEntryLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTournamentEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TournamentEntry To JSON String")
	static FString TournamentEntryToJsonString(const UTournamentEntry* Serializable, const bool Pretty);		
};