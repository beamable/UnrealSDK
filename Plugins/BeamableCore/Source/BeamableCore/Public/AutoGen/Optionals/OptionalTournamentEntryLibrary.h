

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalTournamentEntry.h"

#include "OptionalTournamentEntryLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalTournamentEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalTournamentEntry MakeOptionalTournamentEntry(UTournamentEntry* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TournamentEntry To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalTournamentEntry Conv_OptionalTournamentEntryFromValue(UTournamentEntry* Value);
};
