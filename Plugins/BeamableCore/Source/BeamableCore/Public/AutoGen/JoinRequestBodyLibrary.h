
#pragma once

#include "CoreMinimal.h"
#include "JoinRequestBody.h"

#include "JoinRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UJoinRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize JoinRequestBody To JSON String")
	static FString JoinRequestBodyToJsonString(const UJoinRequestBody* Serializable, const bool Pretty);		
};