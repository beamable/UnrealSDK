
#pragma once

#include "CoreMinimal.h"
#include "PromoteRealmRequestBody.h"

#include "PromoteRealmRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPromoteRealmRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PromoteRealmRequestBody To JSON String")
	static FString PromoteRealmRequestBodyToJsonString(const UPromoteRealmRequestBody* Serializable, const bool Pretty);		
};