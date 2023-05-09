#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FailPurchaseRequestBody.h"

#include "FailPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFailPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - FailPurchaseRequestBody To JSON String")
	static FString FailPurchaseRequestBodyToJsonString(const UFailPurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make FailPurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFailPurchaseRequestBody* Make(int64 Txid, FString Reason, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break FailPurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UFailPurchaseRequestBody* Serializable, int64& Txid, FString& Reason);
};