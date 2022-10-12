
#pragma once

#include "CoreMinimal.h"
#include "PlayerBasicCloudDataRequestBody.h"

#include "PlayerBasicCloudDataRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerBasicCloudDataRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerBasicCloudDataRequestBody To JSON String")
	static FString PlayerBasicCloudDataRequestBodyToJsonString(const UPlayerBasicCloudDataRequestBody* Serializable, const bool Pretty);		
};