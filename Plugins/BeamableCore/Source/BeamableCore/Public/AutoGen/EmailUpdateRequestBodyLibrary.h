#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EmailUpdateRequestBody.h"

#include "EmailUpdateRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEmailUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|4 - Json", DisplayName="EmailUpdateRequestBody To JSON String")
	static FString EmailUpdateRequestBodyToJsonString(const UEmailUpdateRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Make EmailUpdateRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="CodeType, Outer", NativeMakeFunc))
	static UEmailUpdateRequestBody* Make(FString NewEmail, FOptionalString CodeType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Break EmailUpdateRequestBody", meta=(NativeBreakFunc))
	static void Break(const UEmailUpdateRequestBody* Serializable, FString& NewEmail, FOptionalString& CodeType);
};