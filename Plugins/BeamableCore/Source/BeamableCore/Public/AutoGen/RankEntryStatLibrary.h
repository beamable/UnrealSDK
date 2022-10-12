
#pragma once

#include "CoreMinimal.h"
#include "RankEntryStat.h"

#include "RankEntryStatLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URankEntryStatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RankEntryStat To JSON String")
	static FString RankEntryStatToJsonString(const URankEntryStat* Serializable, const bool Pretty);		
};