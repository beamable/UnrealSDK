#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetTotalCouponResponse.h"

#include "GetTotalCouponResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetTotalCouponResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="GetTotalCouponResponse To JSON String")
	static FString GetTotalCouponResponseToJsonString(const UGetTotalCouponResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make GetTotalCouponResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetTotalCouponResponse* Make(int64 Count, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break GetTotalCouponResponse", meta=(NativeBreakFunc))
	static void Break(const UGetTotalCouponResponse* Serializable, int64& Count);
};