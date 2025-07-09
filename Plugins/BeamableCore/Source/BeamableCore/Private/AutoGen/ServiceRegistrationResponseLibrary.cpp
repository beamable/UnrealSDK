
#include "BeamableCore/Public/AutoGen/ServiceRegistrationResponseLibrary.h"

#include "CoreMinimal.h"


FString UServiceRegistrationResponseLibrary::ServiceRegistrationResponseToJsonString(const UServiceRegistrationResponse* Serializable, const bool Pretty)
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

UServiceRegistrationResponse* UServiceRegistrationResponseLibrary::Make(FOptionalArrayOfServiceRegistration Registrations, UObject* Outer)
{
	auto Serializable = NewObject<UServiceRegistrationResponse>(Outer);
	Serializable->Registrations = Registrations;
	
	return Serializable;
}

void UServiceRegistrationResponseLibrary::Break(const UServiceRegistrationResponse* Serializable, FOptionalArrayOfServiceRegistration& Registrations)
{
	Registrations = Serializable->Registrations;
		
}

