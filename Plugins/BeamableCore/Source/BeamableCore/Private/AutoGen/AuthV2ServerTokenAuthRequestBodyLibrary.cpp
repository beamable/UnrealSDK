
#include "BeamableCore/Public/AutoGen/AuthV2ServerTokenAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2ServerTokenAuthRequestBodyLibrary::AuthV2ServerTokenAuthRequestBodyToJsonString(const UAuthV2ServerTokenAuthRequestBody* Serializable, const bool Pretty)
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

UAuthV2ServerTokenAuthRequestBody* UAuthV2ServerTokenAuthRequestBodyLibrary::Make(FOptionalString ClientId, FOptionalString ClientSecret, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2ServerTokenAuthRequestBody>(Outer);
	Serializable->ClientId = ClientId;
	Serializable->ClientSecret = ClientSecret;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	
	return Serializable;
}

void UAuthV2ServerTokenAuthRequestBodyLibrary::Break(const UAuthV2ServerTokenAuthRequestBody* Serializable, FOptionalString& ClientId, FOptionalString& ClientSecret, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ClientId = Serializable->ClientId;
		ClientSecret = Serializable->ClientSecret;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
	}
		
}

