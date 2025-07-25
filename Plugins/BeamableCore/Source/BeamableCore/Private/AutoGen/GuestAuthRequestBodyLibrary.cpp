
#include "BeamableCore/Public/AutoGen/GuestAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGuestAuthRequestBodyLibrary::GuestAuthRequestBodyToJsonString(const UGuestAuthRequestBody* Serializable, const bool Pretty)
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

UGuestAuthRequestBody* UGuestAuthRequestBodyLibrary::Make(FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalContextInfo Context, FOptionalMapOfString InitProperties, UObject* Outer)
{
	auto Serializable = NewObject<UGuestAuthRequestBody>(Outer);
	Serializable->Scope = Scope;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Context = Context;
	Serializable->InitProperties = InitProperties;
	
	return Serializable;
}

void UGuestAuthRequestBodyLibrary::Break(const UGuestAuthRequestBody* Serializable, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalContextInfo& Context, FOptionalMapOfString& InitProperties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Scope = Serializable->Scope;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
		Context = Serializable->Context;
		InitProperties = Serializable->InitProperties;
	}
		
}

