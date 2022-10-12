
#pragma once

#include "CoreMinimal.h"
#include "SendMailObjectRequestBody.h"

#include "SendMailObjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USendMailObjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SendMailObjectRequestBody To JSON String")
	static FString SendMailObjectRequestBodyToJsonString(const USendMailObjectRequestBody* Serializable, const bool Pretty);		
};