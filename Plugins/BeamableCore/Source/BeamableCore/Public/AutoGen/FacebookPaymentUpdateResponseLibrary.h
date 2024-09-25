#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateResponse.h"

#include "FacebookPaymentUpdateResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFacebookPaymentUpdateResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - FacebookPaymentUpdateResponse To JSON String")
	static FString FacebookPaymentUpdateResponseToJsonString(const UFacebookPaymentUpdateResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make FacebookPaymentUpdateResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFacebookPaymentUpdateResponse* Make(FString Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break FacebookPaymentUpdateResponse", meta=(NativeBreakFunc))
	static void Break(const UFacebookPaymentUpdateResponse* Serializable, FString& Result);
};