
#pragma once

#include "CoreMinimal.h"
#include "TokenResponse.h"

#include "TokenResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TokenResponse To JSON String")
	static FString TokenResponseToJsonString(const UTokenResponse* Serializable, const bool Pretty);		
};