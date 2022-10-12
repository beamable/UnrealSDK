
#pragma once

#include "CoreMinimal.h"
#include "GetGroupsRequestBody.h"

#include "GetGroupsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGroupsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetGroupsRequestBody To JSON String")
	static FString GetGroupsRequestBodyToJsonString(const UGetGroupsRequestBody* Serializable, const bool Pretty);		
};