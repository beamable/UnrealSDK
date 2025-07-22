
#include "BeamableCore/Public/AutoGen/PasswordAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPasswordAuthRequestBodyLibrary::PasswordAuthRequestBodyToJsonString(const UPasswordAuthRequestBody* Serializable, const bool Pretty)
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

UPasswordAuthRequestBody* UPasswordAuthRequestBodyLibrary::Make(FOptionalString Email, FOptionalString Password, FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalContextInfo Context, UObject* Outer)
{
	auto Serializable = NewObject<UPasswordAuthRequestBody>(Outer);
	Serializable->Email = Email;
	Serializable->Password = Password;
	Serializable->Scope = Scope;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Context = Context;
	
	return Serializable;
}

void UPasswordAuthRequestBodyLibrary::Break(const UPasswordAuthRequestBody* Serializable, FOptionalString& Email, FOptionalString& Password, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalContextInfo& Context)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Email = Serializable->Email;
		Password = Serializable->Password;
		Scope = Serializable->Scope;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
		Context = Serializable->Context;
	}
		
}

