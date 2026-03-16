
#include "BeamableCore/Public/AutoGen/AuthV2AuthCodeLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2AuthCodeLibrary::AuthV2AuthCodeToJsonString(const UAuthV2AuthCode* Serializable, const bool Pretty)
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

UAuthV2AuthCode* UAuthV2AuthCodeLibrary::Make(FString Code, int64 AccountId, FString RedirectUri, FOptionalDateTime CreatedAt, FOptionalDateTime Ttl, FOptionalArrayOfString Scopes, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2AuthCode>(Outer);
	Serializable->Code = Code;
	Serializable->AccountId = AccountId;
	Serializable->RedirectUri = RedirectUri;
	Serializable->CreatedAt = CreatedAt;
	Serializable->Ttl = Ttl;
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void UAuthV2AuthCodeLibrary::Break(const UAuthV2AuthCode* Serializable, FString& Code, int64& AccountId, FString& RedirectUri, FOptionalDateTime& CreatedAt, FOptionalDateTime& Ttl, FOptionalArrayOfString& Scopes)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Code = Serializable->Code;
		AccountId = Serializable->AccountId;
		RedirectUri = Serializable->RedirectUri;
		CreatedAt = Serializable->CreatedAt;
		Ttl = Serializable->Ttl;
		Scopes = Serializable->Scopes;
	}
		
}

