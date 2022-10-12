
#pragma once

#include "CoreMinimal.h"
#include "NewCustomerResponse.h"

#include "NewCustomerResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UNewCustomerResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize NewCustomerResponse To JSON String")
	static FString NewCustomerResponseToJsonString(const UNewCustomerResponse* Serializable, const bool Pretty);		
};