
#pragma once

#include "CoreMinimal.h"
#include "AccountAvailableResponse.h"

#include "AccountAvailableResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountAvailableResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountAvailableResponse To JSON String")
	static FString AccountAvailableResponseToJsonString(const UAccountAvailableResponse* Serializable, const bool Pretty);		
};