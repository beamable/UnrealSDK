#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/VerifyPurchaseRequestBody.h"

#include "VerifyPurchaseRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UVerifyPurchaseRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - VerifyPurchaseRequestBody To JSON String")
	static FString VerifyPurchaseRequestBodyToJsonString(const UVerifyPurchaseRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make VerifyPurchaseRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UVerifyPurchaseRequestBody* Make(FString Receipt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break VerifyPurchaseRequestBody", meta=(NativeBreakFunc))
	static void Break(const UVerifyPurchaseRequestBody* Serializable, FString& Receipt);
};