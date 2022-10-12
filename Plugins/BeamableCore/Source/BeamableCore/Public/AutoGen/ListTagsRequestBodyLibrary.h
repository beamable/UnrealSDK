
#pragma once

#include "CoreMinimal.h"
#include "ListTagsRequestBody.h"

#include "ListTagsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListTagsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListTagsRequestBody To JSON String")
	static FString ListTagsRequestBodyToJsonString(const UListTagsRequestBody* Serializable, const bool Pretty);		
};