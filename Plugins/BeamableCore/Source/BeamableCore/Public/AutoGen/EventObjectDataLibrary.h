
#pragma once

#include "CoreMinimal.h"
#include "EventObjectData.h"

#include "EventObjectDataLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventObjectDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventObjectData To JSON String")
	static FString EventObjectDataToJsonString(const UEventObjectData* Serializable, const bool Pretty);		
};