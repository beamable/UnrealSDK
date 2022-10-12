

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfStatStringListEntry.h"

#include "OptionalArrayOfStatStringListEntryLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfStatStringListEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfStatStringListEntry MakeOptionalArrayOfStatStringListEntry(TArray<UStatStringListEntry*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UStatStringListEntry*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfStatStringListEntry Conv_OptionalArrayOfStatStringListEntryFromValue(TArray<UStatStringListEntry*> Value);
};
