#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateAccountWithCredsApiResponse.h"

#include "CreateAccountWithCredsApiResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateAccountWithCredsApiResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="CreateAccountWithCredsApiResponse To JSON String")
	static FString CreateAccountWithCredsApiResponseToJsonString(const UCreateAccountWithCredsApiResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make CreateAccountWithCredsApiResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Account, ChallengeToken, Token, Outer", NativeMakeFunc))
	static UCreateAccountWithCredsApiResponse* Make(FOptionalAccountsBasicAccount Account, FOptionalString ChallengeToken, FOptionalTokenResponse Token, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break CreateAccountWithCredsApiResponse", meta=(NativeBreakFunc))
	static void Break(const UCreateAccountWithCredsApiResponse* Serializable, FOptionalAccountsBasicAccount& Account, FOptionalString& ChallengeToken, FOptionalTokenResponse& Token);
};