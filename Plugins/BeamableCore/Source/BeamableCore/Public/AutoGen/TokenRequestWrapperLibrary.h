
#pragma once

#include "CoreMinimal.h"
#include "TokenRequestWrapper.h"

#include "TokenRequestWrapperLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UTokenRequestWrapperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize TokenRequestWrapper To JSON String")
	static FString TokenRequestWrapperToJsonString(const UTokenRequestWrapper* Serializable, const bool Pretty);		
};