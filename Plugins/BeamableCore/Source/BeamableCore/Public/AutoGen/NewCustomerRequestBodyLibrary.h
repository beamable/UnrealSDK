
#pragma once

#include "CoreMinimal.h"
#include "NewCustomerRequestBody.h"

#include "NewCustomerRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UNewCustomerRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize NewCustomerRequestBody To JSON String")
	static FString NewCustomerRequestBodyToJsonString(const UNewCustomerRequestBody* Serializable, const bool Pretty);		
};