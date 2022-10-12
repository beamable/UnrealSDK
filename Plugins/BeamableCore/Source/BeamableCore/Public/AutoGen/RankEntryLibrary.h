
#pragma once

#include "CoreMinimal.h"
#include "RankEntry.h"

#include "RankEntryLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URankEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RankEntry To JSON String")
	static FString RankEntryToJsonString(const URankEntry* Serializable, const bool Pretty);		
};