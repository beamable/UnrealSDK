#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PasswordUpdateRequestBody.h"

#include "PasswordUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPasswordUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PasswordUpdateRequestBody To JSON String")
	static FString PasswordUpdateRequestBodyToJsonString(const UPasswordUpdateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PasswordUpdateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="CodeType, Outer", NativeMakeFunc))
	static UPasswordUpdateRequestBody* Make(FString Email, FOptionalString CodeType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PasswordUpdateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPasswordUpdateRequestBody* Serializable, FString& Email, FOptionalString& CodeType);
};