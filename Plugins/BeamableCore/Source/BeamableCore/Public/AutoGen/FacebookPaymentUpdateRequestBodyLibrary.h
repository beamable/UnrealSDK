#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateRequestBody.h"

#include "FacebookPaymentUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFacebookPaymentUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - FacebookPaymentUpdateRequestBody To JSON String")
	static FString FacebookPaymentUpdateRequestBodyToJsonString(const UFacebookPaymentUpdateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make FacebookPaymentUpdateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFacebookPaymentUpdateRequestBody* Make(FString Object, TArray<UFacebookUpdatedEntry*> Entry, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break FacebookPaymentUpdateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UFacebookPaymentUpdateRequestBody* Serializable, FString& Object, TArray<UFacebookUpdatedEntry*>& Entry);
};