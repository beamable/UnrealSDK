
#include "BeamableCore/Public/AutoGen/AuthV2GuestAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2GuestAuthRequestBodyLibrary::AuthV2GuestAuthRequestBodyToJsonString(const UAuthV2GuestAuthRequestBody* Serializable, const bool Pretty)
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

UAuthV2GuestAuthRequestBody* UAuthV2GuestAuthRequestBodyLibrary::Make(FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, FOptionalMapOfString InitProperties, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2GuestAuthRequestBody>(Outer);
	Serializable->Scope = Scope;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Context = Context;
	Serializable->InitProperties = InitProperties;
	
	return Serializable;
}

void UAuthV2GuestAuthRequestBodyLibrary::Break(const UAuthV2GuestAuthRequestBody* Serializable, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context, FOptionalMapOfString& InitProperties)
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

