
#pragma once

#include "CoreMinimal.h"
#include "Token.h"

#include "TokenLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTokenLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Token To JSON String")
	static FString TokenToJsonString(const UToken* Serializable, const bool Pretty);		
};