
#pragma once

#include "CoreMinimal.h"
#include "CustomerViewResponse.h"

#include "CustomerViewResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCustomerViewResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CustomerViewResponse To JSON String")
	static FString CustomerViewResponseToJsonString(const UCustomerViewResponse* Serializable, const bool Pretty);		
};