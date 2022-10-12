
#pragma once

#include "CoreMinimal.h"
#include "RevokeTokenRequestBody.h"

#include "RevokeTokenRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URevokeTokenRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RevokeTokenRequestBody To JSON String")
	static FString RevokeTokenRequestBodyToJsonString(const URevokeTokenRequestBody* Serializable, const bool Pretty);		
};