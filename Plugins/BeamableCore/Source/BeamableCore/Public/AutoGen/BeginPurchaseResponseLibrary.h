
#pragma once

#include "CoreMinimal.h"
#include "BeginPurchaseResponse.h"

#include "BeginPurchaseResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeginPurchaseResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize BeginPurchaseResponse To JSON String")
	static FString BeginPurchaseResponseToJsonString(const UBeginPurchaseResponse* Serializable, const bool Pretty);		
};