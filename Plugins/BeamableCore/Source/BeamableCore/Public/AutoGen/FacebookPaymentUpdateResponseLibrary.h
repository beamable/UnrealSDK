
#pragma once

#include "CoreMinimal.h"
#include "FacebookPaymentUpdateResponse.h"

#include "FacebookPaymentUpdateResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UFacebookPaymentUpdateResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize FacebookPaymentUpdateResponse To JSON String")
	static FString FacebookPaymentUpdateResponseToJsonString(const UFacebookPaymentUpdateResponse* Serializable, const bool Pretty);		
};