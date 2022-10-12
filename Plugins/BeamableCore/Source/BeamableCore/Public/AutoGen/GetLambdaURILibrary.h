
#pragma once

#include "CoreMinimal.h"
#include "GetLambdaURI.h"

#include "GetLambdaURILibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetLambdaURILibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetLambdaURI To JSON String")
	static FString GetLambdaURIToJsonString(const UGetLambdaURI* Serializable, const bool Pretty);		
};