
#pragma once

#include "CoreMinimal.h"
#include "PlayerIdRequestBody.h"

#include "PlayerIdRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerIdRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerIdRequestBody To JSON String")
	static FString PlayerIdRequestBodyToJsonString(const UPlayerIdRequestBody* Serializable, const bool Pretty);		
};