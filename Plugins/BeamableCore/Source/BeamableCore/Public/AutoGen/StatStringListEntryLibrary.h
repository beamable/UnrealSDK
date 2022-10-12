
#pragma once

#include "CoreMinimal.h"
#include "StatStringListEntry.h"

#include "StatStringListEntryLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStatStringListEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize StatStringListEntry To JSON String")
	static FString StatStringListEntryToJsonString(const UStatStringListEntry* Serializable, const bool Pretty);		
};