
#pragma once

#include "CoreMinimal.h"
#include "AdminGetPlayerStatusRequestBody.h"

#include "AdminGetPlayerStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAdminGetPlayerStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AdminGetPlayerStatusRequestBody To JSON String")
	static FString AdminGetPlayerStatusRequestBodyToJsonString(const UAdminGetPlayerStatusRequestBody* Serializable, const bool Pretty);		
};