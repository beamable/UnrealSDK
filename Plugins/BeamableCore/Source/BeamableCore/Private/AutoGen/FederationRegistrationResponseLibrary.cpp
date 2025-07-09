
#include "BeamableCore/Public/AutoGen/FederationRegistrationResponseLibrary.h"

#include "CoreMinimal.h"


FString UFederationRegistrationResponseLibrary::FederationRegistrationResponseToJsonString(const UFederationRegistrationResponse* Serializable, const bool Pretty)
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

UFederationRegistrationResponse* UFederationRegistrationResponseLibrary::Make(FOptionalArrayOfFederationRegistration Registrations, UObject* Outer)
{
	auto Serializable = NewObject<UFederationRegistrationResponse>(Outer);
	Serializable->Registrations = Registrations;
	
	return Serializable;
}

void UFederationRegistrationResponseLibrary::Break(const UFederationRegistrationResponse* Serializable, FOptionalArrayOfFederationRegistration& Registrations)
{
	Registrations = Serializable->Registrations;
		
}

