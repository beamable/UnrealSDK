
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSGetSamlpeStatResponseLibrary.h"

#include "CoreMinimal.h"


FString ULiveOpsDemoMSGetSamlpeStatResponseLibrary::LiveOpsDemoMSGetSamlpeStatResponseToJsonString(const ULiveOpsDemoMSGetSamlpeStatResponse* Serializable, const bool Pretty)
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

ULiveOpsDemoMSGetSamlpeStatResponse* ULiveOpsDemoMSGetSamlpeStatResponseLibrary::Make(int32 Value, UObject* Outer)
{
	auto Serializable = NewObject<ULiveOpsDemoMSGetSamlpeStatResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void ULiveOpsDemoMSGetSamlpeStatResponseLibrary::Break(const ULiveOpsDemoMSGetSamlpeStatResponse* Serializable, int32& Value)
{
	Value = Serializable->Value;
		
}

