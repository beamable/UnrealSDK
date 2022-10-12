
#pragma once

#include "CoreMinimal.h"
#include "FacebookUpdatedEntry.h"

#include "FacebookUpdatedEntryLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UFacebookUpdatedEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize FacebookUpdatedEntry To JSON String")
	static FString FacebookUpdatedEntryToJsonString(const UFacebookUpdatedEntry* Serializable, const bool Pretty);		
};