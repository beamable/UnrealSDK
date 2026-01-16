#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/VerifyReceiptRequestBody.h"

#include "VerifyReceiptRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UVerifyReceiptRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Json", DisplayName="VerifyReceiptRequestBody To JSON String")
	static FString VerifyReceiptRequestBodyToJsonString(const UVerifyReceiptRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make VerifyReceiptRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Provider, Receipt, Outer", NativeMakeFunc))
	static UVerifyReceiptRequestBody* Make(FOptionalString Provider, FOptionalString Receipt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Break VerifyReceiptRequestBody", meta=(NativeBreakFunc))
	static void Break(const UVerifyReceiptRequestBody* Serializable, FOptionalString& Provider, FOptionalString& Receipt);
};