
#include "BeamableCore/Public/AutoGen/AuthV2DeviceIdAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2DeviceIdAuthRequestBodyLibrary::AuthV2DeviceIdAuthRequestBodyToJsonString(const UAuthV2DeviceIdAuthRequestBody* Serializable, const bool Pretty)
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

UAuthV2DeviceIdAuthRequestBody* UAuthV2DeviceIdAuthRequestBodyLibrary::Make(FOptionalString DeviceId, FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2DeviceIdAuthRequestBody>(Outer);
	Serializable->DeviceId = DeviceId;
	Serializable->Scope = Scope;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Context = Context;
	
	return Serializable;
}

void UAuthV2DeviceIdAuthRequestBodyLibrary::Break(const UAuthV2DeviceIdAuthRequestBody* Serializable, FOptionalString& DeviceId, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		DeviceId = Serializable->DeviceId;
		Scope = Serializable->Scope;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
		Context = Serializable->Context;
	}
		
}

