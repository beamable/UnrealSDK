
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMicroserviceRegistrationsResponseLibrary::MicroserviceRegistrationsResponseToJsonString(const UMicroserviceRegistrationsResponse* Serializable, const bool Pretty)
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

UMicroserviceRegistrationsResponse* UMicroserviceRegistrationsResponseLibrary::Make(TArray<UMicroserviceRegistrations*> Registrations, UObject* Outer)
{
	auto Serializable = NewObject<UMicroserviceRegistrationsResponse>(Outer);
	Serializable->Registrations = Registrations;
	
	return Serializable;
}

void UMicroserviceRegistrationsResponseLibrary::Break(const UMicroserviceRegistrationsResponse* Serializable, TArray<UMicroserviceRegistrations*>& Registrations)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Registrations = Serializable->Registrations;
	}
		
}

