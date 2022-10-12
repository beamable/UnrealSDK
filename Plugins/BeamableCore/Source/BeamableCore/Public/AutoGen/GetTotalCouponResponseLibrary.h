
#pragma once

#include "CoreMinimal.h"
#include "GetTotalCouponResponse.h"

#include "GetTotalCouponResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTotalCouponResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetTotalCouponResponse To JSON String")
	static FString GetTotalCouponResponseToJsonString(const UGetTotalCouponResponse* Serializable, const bool Pretty);		
};