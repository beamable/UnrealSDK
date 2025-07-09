
#include "BeamableCore/Public/AutoGen/FederationRegistrationLibrary.h"

#include "CoreMinimal.h"


FString UFederationRegistrationLibrary::FederationRegistrationToJsonString(const UFederationRegistration* Serializable, const bool Pretty)
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

UFederationRegistration* UFederationRegistrationLibrary::Make(FOptionalBool bTrafficFilterEnabled, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalDateTime Ttl, FOptionalArrayOfSupportedFederation Federation, UObject* Outer)
{
	auto Serializable = NewObject<UFederationRegistration>(Outer);
	Serializable->bTrafficFilterEnabled = bTrafficFilterEnabled;
	Serializable->ServiceName = ServiceName;
	Serializable->RoutingKey = RoutingKey;
	Serializable->Ttl = Ttl;
	Serializable->Federation = Federation;
	
	return Serializable;
}

void UFederationRegistrationLibrary::Break(const UFederationRegistration* Serializable, FOptionalBool& bTrafficFilterEnabled, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalDateTime& Ttl, FOptionalArrayOfSupportedFederation& Federation)
{
	bTrafficFilterEnabled = Serializable->bTrafficFilterEnabled;
	ServiceName = Serializable->ServiceName;
	RoutingKey = Serializable->RoutingKey;
	Ttl = Serializable->Ttl;
	Federation = Serializable->Federation;
		
}

