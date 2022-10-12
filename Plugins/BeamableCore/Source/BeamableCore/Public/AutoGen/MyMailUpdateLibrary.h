
#pragma once

#include "CoreMinimal.h"
#include "MyMailUpdate.h"

#include "MyMailUpdateLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMyMailUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MyMailUpdate To JSON String")
	static FString MyMailUpdateToJsonString(const UMyMailUpdate* Serializable, const bool Pretty);		
};