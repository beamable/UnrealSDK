#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateRequestBody.h"

#include "FacebookPaymentUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFacebookPaymentUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="FacebookPaymentUpdateRequestBody To JSON String")
	static FString FacebookPaymentUpdateRequestBodyToJsonString(const UFacebookPaymentUpdateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make FacebookPaymentUpdateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFacebookPaymentUpdateRequestBody* Make(FString Object, TArray<UFacebookUpdatedEntry*> Entry, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break FacebookPaymentUpdateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UFacebookPaymentUpdateRequestBody* Serializable, FString& Object, TArray<UFacebookUpdatedEntry*>& Entry);
};