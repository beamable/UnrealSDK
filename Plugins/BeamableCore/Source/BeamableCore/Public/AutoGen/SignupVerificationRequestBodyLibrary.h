#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SignupVerificationRequestBody.h"

#include "SignupVerificationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USignupVerificationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="SignupVerificationRequestBody To JSON String")
	static FString SignupVerificationRequestBodyToJsonString(const USignupVerificationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make SignupVerificationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USignupVerificationRequestBody* Make(FString Email, FString Code, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break SignupVerificationRequestBody", meta=(NativeBreakFunc))
	static void Break(const USignupVerificationRequestBody* Serializable, FString& Email, FString& Code);
};