
#include "BeamableCore/Public/AutoGen/TokenRequestWrapperLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTokenRequestWrapperLibrary::TokenRequestWrapperToJsonString(const UTokenRequestWrapper* Serializable, const bool Pretty)
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

UTokenRequestWrapper* UTokenRequestWrapperLibrary::Make(FString GrantType, FOptionalBool bCustomerScoped, FOptionalString DeviceId, FOptionalString ProviderService, FOptionalString Token, FOptionalString Code, FOptionalString ExternalToken, FOptionalChallengeSolution ChallengeSolution, FOptionalString ProviderNamespace, FOptionalString RedirectUri, FOptionalString ThirdParty, FOptionalContextInfo Context, FOptionalString RefreshToken, FOptionalString Username, FOptionalString ClientId, FOptionalString Password, FOptionalArrayOfString Scope, FOptionalMapOfString InitProperties, UObject* Outer)
{
	auto Serializable = NewObject<UTokenRequestWrapper>(Outer);
	Serializable->GrantType = GrantType;
	Serializable->bCustomerScoped = bCustomerScoped;
	Serializable->DeviceId = DeviceId;
	Serializable->ProviderService = ProviderService;
	Serializable->Token = Token;
	Serializable->Code = Code;
	Serializable->ExternalToken = ExternalToken;
	Serializable->ChallengeSolution = ChallengeSolution;
	Serializable->ProviderNamespace = ProviderNamespace;
	Serializable->RedirectUri = RedirectUri;
	Serializable->ThirdParty = ThirdParty;
	Serializable->Context = Context;
	Serializable->RefreshToken = RefreshToken;
	Serializable->Username = Username;
	Serializable->ClientId = ClientId;
	Serializable->Password = Password;
	Serializable->Scope = Scope;
	Serializable->InitProperties = InitProperties;
	
	return Serializable;
}

void UTokenRequestWrapperLibrary::Break(const UTokenRequestWrapper* Serializable, FString& GrantType, FOptionalBool& bCustomerScoped, FOptionalString& DeviceId, FOptionalString& ProviderService, FOptionalString& Token, FOptionalString& Code, FOptionalString& ExternalToken, FOptionalChallengeSolution& ChallengeSolution, FOptionalString& ProviderNamespace, FOptionalString& RedirectUri, FOptionalString& ThirdParty, FOptionalContextInfo& Context, FOptionalString& RefreshToken, FOptionalString& Username, FOptionalString& ClientId, FOptionalString& Password, FOptionalArrayOfString& Scope, FOptionalMapOfString& InitProperties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GrantType = Serializable->GrantType;
		bCustomerScoped = Serializable->bCustomerScoped;
		DeviceId = Serializable->DeviceId;
		ProviderService = Serializable->ProviderService;
		Token = Serializable->Token;
		Code = Serializable->Code;
		ExternalToken = Serializable->ExternalToken;
		ChallengeSolution = Serializable->ChallengeSolution;
		ProviderNamespace = Serializable->ProviderNamespace;
		RedirectUri = Serializable->RedirectUri;
		ThirdParty = Serializable->ThirdParty;
		Context = Serializable->Context;
		RefreshToken = Serializable->RefreshToken;
		Username = Serializable->Username;
		ClientId = Serializable->ClientId;
		Password = Serializable->Password;
		Scope = Serializable->Scope;
		InitProperties = Serializable->InitProperties;
	}
		
}

