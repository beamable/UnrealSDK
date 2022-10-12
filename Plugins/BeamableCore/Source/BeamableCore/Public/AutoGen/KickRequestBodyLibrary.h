
#pragma once

#include "CoreMinimal.h"
#include "KickRequestBody.h"

#include "KickRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UKickRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize KickRequestBody To JSON String")
	static FString KickRequestBodyToJsonString(const UKickRequestBody* Serializable, const bool Pretty);		
};