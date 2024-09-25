#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/CancelPurchaseRequestBody.h"

#include "CancelPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCancelPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CancelPurchaseRequestBody To JSON String")
	static FString CancelPurchaseRequestBodyToJsonString(const UCancelPurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CancelPurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCancelPurchaseRequestBody* Make(int64 Txid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CancelPurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCancelPurchaseRequestBody* Serializable, int64& Txid);
};