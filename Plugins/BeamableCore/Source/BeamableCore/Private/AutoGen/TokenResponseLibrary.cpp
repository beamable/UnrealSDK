
#include "AutoGen/TokenResponseLibrary.h"

#include "CoreMinimal.h"


FString UTokenResponseLibrary::TokenResponseToJsonString(const UTokenResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UTokenResponse* UTokenResponseLibrary::Make(FString AccessToken, int64 ExpiresIn, FString RefreshToken, FString TokenType, FOptionalArrayOfString Scopes, UObject* Outer)
{
	auto Serializable = NewObject<UTokenResponse>(Outer);
	Serializable->AccessToken = AccessToken;
	Serializable->ExpiresIn = ExpiresIn;
	Serializable->RefreshToken = RefreshToken;
	Serializable->TokenType = TokenType;
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void UTokenResponseLibrary::Break(const UTokenResponse* Serializable, FString& AccessToken, int64& ExpiresIn, FString& RefreshToken, FString& TokenType, FOptionalArrayOfString& Scopes)
{
	AccessToken = Serializable->AccessToken;
	ExpiresIn = Serializable->ExpiresIn;
	RefreshToken = Serializable->RefreshToken;
	TokenType = Serializable->TokenType;
	Scopes = Serializable->Scopes;
		
}

