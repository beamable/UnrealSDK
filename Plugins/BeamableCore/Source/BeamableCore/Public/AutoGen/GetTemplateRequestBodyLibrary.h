
#pragma once

#include "CoreMinimal.h"
#include "GetTemplateRequestBody.h"

#include "GetTemplateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTemplateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetTemplateRequestBody To JSON String")
	static FString GetTemplateRequestBodyToJsonString(const UGetTemplateRequestBody* Serializable, const bool Pretty);		
};