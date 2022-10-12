
#pragma once

#include "CoreMinimal.h"
#include "GiveCouponReq.h"

#include "GiveCouponReqLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGiveCouponReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GiveCouponReq To JSON String")
	static FString GiveCouponReqToJsonString(const UGiveCouponReq* Serializable, const bool Pretty);		
};