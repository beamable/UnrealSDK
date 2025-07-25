
#include "BeamableCore/Public/AutoGen/ServerTokenAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServerTokenAuthRequestBodyLibrary::ServerTokenAuthRequestBodyToJsonString(const UServerTokenAuthRequestBody* Serializable, const bool Pretty)
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

UServerTokenAuthRequestBody* UServerTokenAuthRequestBodyLibrary::Make(FOptionalString ClientId, FOptionalString ClientSecret, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, UObject* Outer)
{
	auto Serializable = NewObject<UServerTokenAuthRequestBody>(Outer);
	Serializable->ClientId = ClientId;
	Serializable->ClientSecret = ClientSecret;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	
	return Serializable;
}

void UServerTokenAuthRequestBodyLibrary::Break(const UServerTokenAuthRequestBody* Serializable, FOptionalString& ClientId, FOptionalString& ClientSecret, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ClientId = Serializable->ClientId;
		ClientSecret = Serializable->ClientSecret;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
	}
		
}

