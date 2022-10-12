
#pragma once

#include "CoreMinimal.h"
#include "PlayerStatusUpdate.h"

#include "PlayerStatusUpdateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerStatusUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerStatusUpdate To JSON String")
	static FString PlayerStatusUpdateToJsonString(const UPlayerStatusUpdate* Serializable, const bool Pretty);		
};