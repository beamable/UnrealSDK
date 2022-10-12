
#pragma once

#include "CoreMinimal.h"
#include "PasswordUpdateRequestBody.h"

#include "PasswordUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPasswordUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PasswordUpdateRequestBody To JSON String")
	static FString PasswordUpdateRequestBodyToJsonString(const UPasswordUpdateRequestBody* Serializable, const bool Pretty);		
};