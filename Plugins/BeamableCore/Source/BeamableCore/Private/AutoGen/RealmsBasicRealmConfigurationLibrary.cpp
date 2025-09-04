
#include "BeamableCore/Public/AutoGen/RealmsBasicRealmConfigurationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicRealmConfigurationLibrary::RealmsBasicRealmConfigurationToJsonString(const URealmsBasicRealmConfiguration* Serializable, const bool Pretty)
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

URealmsBasicRealmConfiguration* URealmsBasicRealmConfigurationLibrary::Make(UWebSocketConfiguration* WebsocketConfig, FString MicroserviceURI, FString PortalURI, FString MicroserviceEcrURI, FString StorageBrowserURI, FString Environment, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicRealmConfiguration>(Outer);
	Serializable->WebsocketConfig = WebsocketConfig;
	Serializable->MicroserviceURI = MicroserviceURI;
	Serializable->PortalURI = PortalURI;
	Serializable->MicroserviceEcrURI = MicroserviceEcrURI;
	Serializable->StorageBrowserURI = StorageBrowserURI;
	Serializable->Environment = Environment;
	
	return Serializable;
}

void URealmsBasicRealmConfigurationLibrary::Break(const URealmsBasicRealmConfiguration* Serializable, UWebSocketConfiguration*& WebsocketConfig, FString& MicroserviceURI, FString& PortalURI, FString& MicroserviceEcrURI, FString& StorageBrowserURI, FString& Environment)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		WebsocketConfig = Serializable->WebsocketConfig;
		MicroserviceURI = Serializable->MicroserviceURI;
		PortalURI = Serializable->PortalURI;
		MicroserviceEcrURI = Serializable->MicroserviceEcrURI;
		StorageBrowserURI = Serializable->StorageBrowserURI;
		Environment = Serializable->Environment;
	}
		
}

