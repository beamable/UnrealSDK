
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

UCreateAccountWithCredsApiResponse* UCreateAccountWithCredsApiResponseLibrary::Make(FOptionalAccountsBasicAccount Account, FOptionalString ChallengeToken, FOptionalTokenResponse Token, UObject* Outer)
{
	auto Serializable = NewObject<UCreateAccountWithCredsApiResponse>(Outer);
	Serializable->Account = Account;
	Serializable->ChallengeToken = ChallengeToken;
	Serializable->Token = Token;
	
	return Serializable;
}

void UCreateAccountWithCredsApiResponseLibrary::Break(const UCreateAccountWithCredsApiResponse* Serializable, FOptionalAccountsBasicAccount& Account, FOptionalString& ChallengeToken, FOptionalTokenResponse& Token)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Account = Serializable->Account;
		ChallengeToken = Serializable->ChallengeToken;
		Token = Serializable->Token;
	}
		
}

