

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalRankEntry.h"

#include "OptionalRankEntryLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalRankEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalRankEntry MakeOptionalRankEntry(URankEntry* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "RankEntry To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalRankEntry Conv_OptionalRankEntryFromValue(URankEntry* Value);
};
