
#include "BeamableCore/Public/AutoGen/AuthV2AuthCodeRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2AuthCodeRequestBodyLibrary::AuthV2AuthCodeRequestBodyToJsonString(const UAuthV2AuthCodeRequestBody* Serializable, const bool Pretty)
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

UAuthV2AuthCodeRequestBody* UAuthV2AuthCodeRequestBodyLibrary::Make(FOptionalBeamAccountId AccountId, FOptionalString RedirectUri, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, FOptionalArrayOfString Scopes, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2AuthCodeRequestBody>(Outer);
	Serializable->AccountId = AccountId;
	Serializable->RedirectUri = RedirectUri;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Context = Context;
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void UAuthV2AuthCodeRequestBodyLibrary::Break(const UAuthV2AuthCodeRequestBody* Serializable, FOptionalBeamAccountId& AccountId, FOptionalString& RedirectUri, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context, FOptionalArrayOfString& Scopes)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		AccountId = Serializable->AccountId;
		RedirectUri = Serializable->RedirectUri;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
		Context = Serializable->Context;
		Scopes = Serializable->Scopes;
	}
		
}

