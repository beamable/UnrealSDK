
#pragma once

#include "CoreMinimal.h"
#include "CustomerView.h"

#include "CustomerViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCustomerViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CustomerView To JSON String")
	static FString CustomerViewToJsonString(const UCustomerView* Serializable, const bool Pretty);		
};