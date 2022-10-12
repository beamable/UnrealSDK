
#pragma once

#include "CoreMinimal.h"
#include "DeleteRoleRequestBody.h"

#include "DeleteRoleRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteRoleRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DeleteRoleRequestBody To JSON String")
	static FString DeleteRoleRequestBodyToJsonString(const UDeleteRoleRequestBody* Serializable, const bool Pretty);		
};