
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/ChatGetRequestBody.h"

#include "ChatGetRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UChatGetRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ChatGetRequestBody To JSON String")
	static FString ChatGetRequestBodyToJsonString(const UChatGetRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ChatGetRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scope, Outer", NativeMakeFunc))
	static UChatGetRequestBody* Make(FOptionalString Scope, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ChatGetRequestBody", meta=(NativeBreakFunc))
	static void Break(const UChatGetRequestBody* Serializable, FOptionalString& Scope);
};