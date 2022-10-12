
#pragma once

#include "CoreMinimal.h"
#include "ListTokenResponse.h"

#include "ListTokenResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UListTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ListTokenResponse To JSON String")
	static FString ListTokenResponseToJsonString(const UListTokenResponse* Serializable, const bool Pretty);		
};