
#include "BeamableCore/Public/AutoGen/SupportedFederationRegistrationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USupportedFederationRegistrationLibrary::SupportedFederationRegistrationToJsonString(const USupportedFederationRegistration* Serializable, const bool Pretty)
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

USupportedFederationRegistration* USupportedFederationRegistrationLibrary::Make(bool bTrafficFilterEnabled, FString ServiceName, FOptionalString RoutingKey, FOptionalArrayOfSupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<USupportedFederationRegistration>(Outer);
	Serializable->bTrafficFilterEnabled = bTrafficFilterEnabled;
	Serializable->ServiceName = ServiceName;
	Serializable->RoutingKey = RoutingKey;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void USupportedFederationRegistrationLibrary::Break(const USupportedFederationRegistration* Serializable, bool& bTrafficFilterEnabled, FString& ServiceName, FOptionalString& RoutingKey, FOptionalArrayOfSupportedFederation& Federation)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bTrafficFilterEnabled = Serializable->bTrafficFilterEnabled;
		ServiceName = Serializable->ServiceName;
		RoutingKey = Serializable->RoutingKey;
		Federation = Serializable->Federation;
	}
		
}

