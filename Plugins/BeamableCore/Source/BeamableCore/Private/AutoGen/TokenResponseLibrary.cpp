
#include "BeamableCore/Public/AutoGen/TokenResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTokenResponseLibrary::TokenResponseToJsonString(const UTokenResponse* Serializable, const bool Pretty)
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

UTokenResponse* UTokenResponseLibrary::Make(int64 ExpiresIn, FString TokenType, FOptionalString AccessToken, FOptionalString RefreshToken, FOptionalString ChallengeToken, FOptionalArrayOfString Scopes, UObject* Outer)
{
	auto Serializable = NewObject<UTokenResponse>(Outer);
	Serializable->ExpiresIn = ExpiresIn;
	Serializable->TokenType = TokenType;
	Serializable->AccessToken = AccessToken;
	Serializable->RefreshToken = RefreshToken;
	Serializable->ChallengeToken = ChallengeToken;
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void UTokenResponseLibrary::Break(const UTokenResponse* Serializable, int64& ExpiresIn, FString& TokenType, FOptionalString& AccessToken, FOptionalString& RefreshToken, FOptionalString& ChallengeToken, FOptionalArrayOfString& Scopes)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ExpiresIn = Serializable->ExpiresIn;
		TokenType = Serializable->TokenType;
		AccessToken = Serializable->AccessToken;
		RefreshToken = Serializable->RefreshToken;
		ChallengeToken = Serializable->ChallengeToken;
		Scopes = Serializable->Scopes;
	}
		
}

