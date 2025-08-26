
#include "BeamableCore/Public/AutoGen/CustomerActorRealmConfigurationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorRealmConfigurationLibrary::CustomerActorRealmConfigurationToJsonString(const UCustomerActorRealmConfiguration* Serializable, const bool Pretty)
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

UCustomerActorRealmConfiguration* UCustomerActorRealmConfigurationLibrary::Make(FString Environment, UWebSocketConfiguration* WebsocketConfig, FString MicroserviceUri, FString MicroserviceEcrUri, FString PortalUri, FString StorageBrowserUri, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorRealmConfiguration>(Outer);
	Serializable->Environment = Environment;
	Serializable->WebsocketConfig = WebsocketConfig;
	Serializable->MicroserviceUri = MicroserviceUri;
	Serializable->MicroserviceEcrUri = MicroserviceEcrUri;
	Serializable->PortalUri = PortalUri;
	Serializable->StorageBrowserUri = StorageBrowserUri;
	
	return Serializable;
}

void UCustomerActorRealmConfigurationLibrary::Break(const UCustomerActorRealmConfiguration* Serializable, FString& Environment, UWebSocketConfiguration*& WebsocketConfig, FString& MicroserviceUri, FString& MicroserviceEcrUri, FString& PortalUri, FString& StorageBrowserUri)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Environment = Serializable->Environment;
		WebsocketConfig = Serializable->WebsocketConfig;
		MicroserviceUri = Serializable->MicroserviceUri;
		MicroserviceEcrUri = Serializable->MicroserviceEcrUri;
		PortalUri = Serializable->PortalUri;
		StorageBrowserUri = Serializable->StorageBrowserUri;
	}
		
}

