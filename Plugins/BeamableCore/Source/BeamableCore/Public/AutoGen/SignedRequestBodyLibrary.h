#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SignedRequestBody.h"

#include "SignedRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USignedRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="SignedRequestBody To JSON String")
	static FString SignedRequestBodyToJsonString(const USignedRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make SignedRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Url, Body, Method, Headers, Outer", NativeMakeFunc))
	static USignedRequestBody* Make(FOptionalString Url, FOptionalString Body, FOptionalString Method, FOptionalArrayOfStringStringKeyValuePair Headers, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break SignedRequestBody", meta=(NativeBreakFunc))
	static void Break(const USignedRequestBody* Serializable, FOptionalString& Url, FOptionalString& Body, FOptionalString& Method, FOptionalArrayOfStringStringKeyValuePair& Headers);
};