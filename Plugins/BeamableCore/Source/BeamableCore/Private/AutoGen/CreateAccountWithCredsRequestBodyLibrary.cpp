
#include "BeamableCore/Public/AutoGen/CreateAccountWithCredsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateAccountWithCredsRequestBodyLibrary::CreateAccountWithCredsRequestBodyToJsonString(const UCreateAccountWithCredsRequestBody* Serializable, const bool Pretty)
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

UCreateAccountWithCredsRequestBody* UCreateAccountWithCredsRequestBodyLibrary::Make(FOptionalString Username, FOptionalString ProviderNamespace, FOptionalChallengeSolution ChallengeSolution, FOptionalString ExternalToken, FOptionalString ProviderService, FOptionalString Password, FOptionalMapOfString InitProperties, UObject* Outer)
{
	auto Serializable = NewObject<UCreateAccountWithCredsRequestBody>(Outer);
	Serializable->Username = Username;
	Serializable->ProviderNamespace = ProviderNamespace;
	Serializable->ChallengeSolution = ChallengeSolution;
	Serializable->ExternalToken = ExternalToken;
	Serializable->ProviderService = ProviderService;
	Serializable->Password = Password;
	Serializable->InitProperties = InitProperties;
	
	return Serializable;
}

void UCreateAccountWithCredsRequestBodyLibrary::Break(const UCreateAccountWithCredsRequestBody* Serializable, FOptionalString& Username, FOptionalString& ProviderNamespace, FOptionalChallengeSolution& ChallengeSolution, FOptionalString& ExternalToken, FOptionalString& ProviderService, FOptionalString& Password, FOptionalMapOfString& InitProperties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Username = Serializable->Username;
		ProviderNamespace = Serializable->ProviderNamespace;
		ChallengeSolution = Serializable->ChallengeSolution;
		ExternalToken = Serializable->ExternalToken;
		ProviderService = Serializable->ProviderService;
		Password = Serializable->Password;
		InitProperties = Serializable->InitProperties;
	}
		
}

