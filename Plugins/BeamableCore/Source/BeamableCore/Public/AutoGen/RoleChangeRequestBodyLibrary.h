
#pragma once

#include "CoreMinimal.h"
#include "RoleChangeRequestBody.h"

#include "RoleChangeRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URoleChangeRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RoleChangeRequestBody To JSON String")
	static FString RoleChangeRequestBodyToJsonString(const URoleChangeRequestBody* Serializable, const bool Pretty);		
};