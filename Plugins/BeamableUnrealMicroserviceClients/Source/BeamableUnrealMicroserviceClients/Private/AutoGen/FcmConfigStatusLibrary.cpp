
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/FcmConfigStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UFcmConfigStatusLibrary::FcmConfigStatusToJsonString(const UFcmConfigStatus* Serializable, const bool Pretty)
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

UFcmConfigStatus* UFcmConfigStatusLibrary::Make(bool bConfigured, bool bPrivateKeyLoaded, FString ProjectId, FString ClientEmail, FString TokenUri, FString Message, UObject* Outer)
{
	auto Serializable = NewObject<UFcmConfigStatus>(Outer);
	Serializable->bConfigured = bConfigured;
	Serializable->bPrivateKeyLoaded = bPrivateKeyLoaded;
	Serializable->ProjectId = ProjectId;
	Serializable->ClientEmail = ClientEmail;
	Serializable->TokenUri = TokenUri;
	Serializable->Message = Message;
	
	return Serializable;
}

void UFcmConfigStatusLibrary::Break(const UFcmConfigStatus* Serializable, bool& bConfigured, bool& bPrivateKeyLoaded, FString& ProjectId, FString& ClientEmail, FString& TokenUri, FString& Message)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bConfigured = Serializable->bConfigured;
		bPrivateKeyLoaded = Serializable->bPrivateKeyLoaded;
		ProjectId = Serializable->ProjectId;
		ClientEmail = Serializable->ClientEmail;
		TokenUri = Serializable->TokenUri;
		Message = Serializable->Message;
	}
		
}

