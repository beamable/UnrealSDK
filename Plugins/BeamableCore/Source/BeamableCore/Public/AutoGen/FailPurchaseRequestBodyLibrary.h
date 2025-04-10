#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FailPurchaseRequestBody.h"

#include "FailPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFailPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|4 - Json", DisplayName="FailPurchaseRequestBody To JSON String")
	static FString FailPurchaseRequestBodyToJsonString(const UFailPurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|3 - Backend", DisplayName="Make FailPurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFailPurchaseRequestBody* Make(int64 Txid, FString Reason, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|3 - Backend", DisplayName="Break FailPurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UFailPurchaseRequestBody* Serializable, int64& Txid, FString& Reason);
};