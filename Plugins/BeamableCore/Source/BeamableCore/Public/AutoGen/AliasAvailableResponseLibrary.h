
#pragma once

#include "CoreMinimal.h"
#include "AliasAvailableResponse.h"

#include "AliasAvailableResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAliasAvailableResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AliasAvailableResponse To JSON String")
	static FString AliasAvailableResponseToJsonString(const UAliasAvailableResponse* Serializable, const bool Pretty);		
};