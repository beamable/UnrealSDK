
#pragma once

#include "CoreMinimal.h"
#include "GetSocialStatusesRequestBody.h"

#include "GetSocialStatusesRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSocialStatusesRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetSocialStatusesRequestBody To JSON String")
	static FString GetSocialStatusesRequestBodyToJsonString(const UGetSocialStatusesRequestBody* Serializable, const bool Pretty);		
};