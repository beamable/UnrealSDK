
#include "AutoGen/TokenRequestWrapperLibrary.h"

#include "CoreMinimal.h"


FString UTokenRequestWrapperLibrary::TokenRequestWrapperToJsonString(const UTokenRequestWrapper* Serializable, const bool Pretty)
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

UTokenRequestWrapper* UTokenRequestWrapperLibrary::Make(FString GrantType, FOptionalBool bCustomerScoped, FOptionalString DeviceId, FOptionalString Username, FOptionalString RefreshToken, FOptionalContextInfo Context, FOptionalString ThirdParty, FOptionalString RedirectUri, FOptionalString ClientId, FOptionalString Code, FOptionalString Token, FOptionalString Password, FOptionalArrayOfString Scope, UObject* Outer)
{
	auto Serializable = NewObject<UTokenRequestWrapper>(Outer);
	Serializable->GrantType = GrantType;
	Serializable->bCustomerScoped = bCustomerScoped;
	Serializable->DeviceId = DeviceId;
	Serializable->Username = Username;
	Serializable->RefreshToken = RefreshToken;
	Serializable->Context = Context;
	Serializable->ThirdParty = ThirdParty;
	Serializable->RedirectUri = RedirectUri;
	Serializable->ClientId = ClientId;
	Serializable->Code = Code;
	Serializable->Token = Token;
	Serializable->Password = Password;
	Serializable->Scope = Scope;
	
	return Serializable;
}

void UTokenRequestWrapperLibrary::Break(const UTokenRequestWrapper* Serializable, FString& GrantType, FOptionalBool& bCustomerScoped, FOptionalString& DeviceId, FOptionalString& Username, FOptionalString& RefreshToken, FOptionalContextInfo& Context, FOptionalString& ThirdParty, FOptionalString& RedirectUri, FOptionalString& ClientId, FOptionalString& Code, FOptionalString& Token, FOptionalString& Password, FOptionalArrayOfString& Scope)
{
	GrantType = Serializable->GrantType;
	bCustomerScoped = Serializable->bCustomerScoped;
	DeviceId = Serializable->DeviceId;
	Username = Serializable->Username;
	RefreshToken = Serializable->RefreshToken;
	Context = Serializable->Context;
	ThirdParty = Serializable->ThirdParty;
	RedirectUri = Serializable->RedirectUri;
	ClientId = Serializable->ClientId;
	Code = Serializable->Code;
	Token = Serializable->Token;
	Password = Serializable->Password;
	Scope = Serializable->Scope;
		
}

