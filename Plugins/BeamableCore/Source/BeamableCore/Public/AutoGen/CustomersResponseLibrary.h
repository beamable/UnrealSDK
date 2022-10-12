
#pragma once

#include "CoreMinimal.h"
#include "CustomersResponse.h"

#include "CustomersResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCustomersResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CustomersResponse To JSON String")
	static FString CustomersResponseToJsonString(const UCustomersResponse* Serializable, const bool Pretty);		
};