
#pragma once

#include "CoreMinimal.h"
#include "NewGameRequestBody.h"

#include "NewGameRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UNewGameRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize NewGameRequestBody To JSON String")
	static FString NewGameRequestBodyToJsonString(const UNewGameRequestBody* Serializable, const bool Pretty);		
};