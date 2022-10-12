
#pragma once

#include "CoreMinimal.h"
#include "ThirdPartyAvailableRequestBody.h"

#include "ThirdPartyAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UThirdPartyAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ThirdPartyAvailableRequestBody To JSON String")
	static FString ThirdPartyAvailableRequestBodyToJsonString(const UThirdPartyAvailableRequestBody* Serializable, const bool Pretty);		
};