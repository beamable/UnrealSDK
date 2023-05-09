#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GiveCouponReq.h"

#include "GiveCouponReqLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGiveCouponReqLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GiveCouponReq To JSON String")
	static FString GiveCouponReqToJsonString(const UGiveCouponReq* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GiveCouponReq", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGiveCouponReq* Make(FString Listing, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GiveCouponReq", meta=(NativeBreakFunc))
	static void Break(const UGiveCouponReq* Serializable, FString& Listing);
};