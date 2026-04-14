
#include "BeamableCore/Public/AutoGen/AuthV2AuthorizationCodeAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2AuthorizationCodeAuthRequestBodyLibrary::AuthV2AuthorizationCodeAuthRequestBodyToJsonString(const UAuthV2AuthorizationCodeAuthRequestBody* Serializable, const bool Pretty)
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

UAuthV2AuthorizationCodeAuthRequestBody* UAuthV2AuthorizationCodeAuthRequestBodyLibrary::Make(FOptionalString ClientId, FOptionalString Code, FOptionalString RedirectUri, FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2AuthorizationCodeAuthRequestBody>(Outer);
	Serializable->ClientId = ClientId;
	Serializable->Code = Code;
	Serializable->RedirectUri = RedirectUri;
	Serializable->Scope = Scope;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Context = Context;
	
	return Serializable;
}

void UAuthV2AuthorizationCodeAuthRequestBodyLibrary::Break(const UAuthV2AuthorizationCodeAuthRequestBody* Serializable, FOptionalString& ClientId, FOptionalString& Code, FOptionalString& RedirectUri, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ClientId = Serializable->ClientId;
		Code = Serializable->Code;
		RedirectUri = Serializable->RedirectUri;
		Scope = Serializable->Scope;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
		Context = Serializable->Context;
	}
		
}

