#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AccountAvailableRequestBody.h"

#include "AccountAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AccountAvailableRequestBody To JSON String")
	static FString AccountAvailableRequestBodyToJsonString(const UAccountAvailableRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AccountAvailableRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAccountAvailableRequestBody* Make(FString Email, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AccountAvailableRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAccountAvailableRequestBody* Serializable, FString& Email);
};