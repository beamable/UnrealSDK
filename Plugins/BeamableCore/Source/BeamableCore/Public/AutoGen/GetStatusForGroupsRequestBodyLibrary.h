
#pragma once

#include "CoreMinimal.h"
#include "GetStatusForGroupsRequestBody.h"

#include "GetStatusForGroupsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStatusForGroupsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetStatusForGroupsRequestBody To JSON String")
	static FString GetStatusForGroupsRequestBodyToJsonString(const UGetStatusForGroupsRequestBody* Serializable, const bool Pretty);		
};