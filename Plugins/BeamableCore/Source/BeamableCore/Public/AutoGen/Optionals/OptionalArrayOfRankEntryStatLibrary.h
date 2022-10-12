

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfRankEntryStat.h"

#include "OptionalArrayOfRankEntryStatLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfRankEntryStatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfRankEntryStat MakeOptionalArrayOfRankEntryStat(TArray<URankEntryStat*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<URankEntryStat*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfRankEntryStat Conv_OptionalArrayOfRankEntryStatFromValue(TArray<URankEntryStat*> Value);
};
