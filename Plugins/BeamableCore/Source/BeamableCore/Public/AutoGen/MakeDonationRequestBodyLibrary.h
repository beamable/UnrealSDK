
#pragma once

#include "CoreMinimal.h"
#include "MakeDonationRequestBody.h"

#include "MakeDonationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMakeDonationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MakeDonationRequestBody To JSON String")
	static FString MakeDonationRequestBodyToJsonString(const UMakeDonationRequestBody* Serializable, const bool Pretty);		
};