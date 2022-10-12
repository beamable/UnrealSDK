
#pragma once

#include "CoreMinimal.h"
#include "CustomerResponse.h"

#include "CustomerResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCustomerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CustomerResponse To JSON String")
	static FString CustomerResponseToJsonString(const UCustomerResponse* Serializable, const bool Pretty);		
};