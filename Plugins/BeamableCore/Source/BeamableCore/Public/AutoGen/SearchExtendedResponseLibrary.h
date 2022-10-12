
#pragma once

#include "CoreMinimal.h"
#include "SearchExtendedResponse.h"

#include "SearchExtendedResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USearchExtendedResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SearchExtendedResponse To JSON String")
	static FString SearchExtendedResponseToJsonString(const USearchExtendedResponse* Serializable, const bool Pretty);		
};