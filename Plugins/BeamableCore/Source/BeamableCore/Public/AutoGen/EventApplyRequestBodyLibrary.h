
#pragma once

#include "CoreMinimal.h"
#include "EventApplyRequestBody.h"

#include "EventApplyRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventApplyRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventApplyRequestBody To JSON String")
	static FString EventApplyRequestBodyToJsonString(const UEventApplyRequestBody* Serializable, const bool Pretty);		
};