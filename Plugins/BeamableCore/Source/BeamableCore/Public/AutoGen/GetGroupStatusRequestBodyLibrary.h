
#pragma once

#include "CoreMinimal.h"
#include "GetGroupStatusRequestBody.h"

#include "GetGroupStatusRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGroupStatusRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetGroupStatusRequestBody To JSON String")
	static FString GetGroupStatusRequestBodyToJsonString(const UGetGroupStatusRequestBody* Serializable, const bool Pretty);		
};