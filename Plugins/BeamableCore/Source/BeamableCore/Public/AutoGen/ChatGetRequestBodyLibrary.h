
#pragma once

#include "CoreMinimal.h"
#include "ChatGetRequestBody.h"

#include "ChatGetRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UChatGetRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ChatGetRequestBody To JSON String")
	static FString ChatGetRequestBodyToJsonString(const UChatGetRequestBody* Serializable, const bool Pretty);		
};