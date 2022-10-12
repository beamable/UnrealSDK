
#pragma once

#include "CoreMinimal.h"
#include "ListTagsResponse.h"

#include "ListTagsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListTagsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListTagsResponse To JSON String")
	static FString ListTagsResponseToJsonString(const UListTagsResponse* Serializable, const bool Pretty);		
};