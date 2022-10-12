
#pragma once

#include "CoreMinimal.h"
#include "RemoveLaunchMessageRequestBody.h"

#include "RemoveLaunchMessageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URemoveLaunchMessageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RemoveLaunchMessageRequestBody To JSON String")
	static FString RemoveLaunchMessageRequestBodyToJsonString(const URemoveLaunchMessageRequestBody* Serializable, const bool Pretty);		
};