#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SignupVerificationResponse.h"

#include "SignupVerificationResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USignupVerificationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="SignupVerificationResponse To JSON String")
	static FString SignupVerificationResponseToJsonString(const USignupVerificationResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make SignupVerificationResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USignupVerificationResponse* Make(UAccountPlayerView* Account, UTokenResponse* Token, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break SignupVerificationResponse", meta=(NativeBreakFunc))
	static void Break(const USignupVerificationResponse* Serializable, UAccountPlayerView*& Account, UTokenResponse*& Token);
};