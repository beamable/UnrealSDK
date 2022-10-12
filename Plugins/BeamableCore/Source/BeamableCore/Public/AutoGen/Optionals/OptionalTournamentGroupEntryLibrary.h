

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalTournamentGroupEntry.h"

#include "OptionalTournamentGroupEntryLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalTournamentGroupEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalTournamentGroupEntry MakeOptionalTournamentGroupEntry(UTournamentGroupEntry* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TournamentGroupEntry To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalTournamentGroupEntry Conv_OptionalTournamentGroupEntryFromValue(UTournamentGroupEntry* Value);
};
