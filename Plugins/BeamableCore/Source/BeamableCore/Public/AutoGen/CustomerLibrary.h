
#pragma once

#include "CoreMinimal.h"
#include "Customer.h"

#include "CustomerLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCustomerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Customer To JSON String")
	static FString CustomerToJsonString(const UCustomer* Serializable, const bool Pretty);		
};