
#include "BeamableCore/Public/AutoGen/CreateAccountWithCredsApiResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateAccountWithCredsApiResponseLibrary::CreateAccountWithCredsApiResponseToJsonString(const UCreateAccountWithCredsApiResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UCreateAccountWithCredsApiResponse* UCreateAccountWithCredsApiResponseLibrary::Make(FOptionalAccountPlayerView Account, FOptionalString ChallengeToken, FOptionalTokenResponse Token, FOptionalString VerificationRequired, UObject* Outer)
{
	auto Serializable = NewObject<UCreateAccountWithCredsApiResponse>(Outer);
	Serializable->Account = Account;
	Serializable->ChallengeToken = ChallengeToken;
	Serializable->Token = Token;
	Serializable->VerificationRequired = VerificationRequired;
	
	return Serializable;
}

void UCreateAccountWithCredsApiResponseLibrary::Break(const UCreateAccountWithCredsApiResponse* Serializable, FOptionalAccountPlayerView& Account, FOptionalString& ChallengeToken, FOptionalTokenResponse& Token, FOptionalString& VerificationRequired)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Account = Serializable->Account;
		ChallengeToken = Serializable->ChallengeToken;
		Token = Serializable->Token;
		VerificationRequired = Serializable->VerificationRequired;
	}
		
}

