
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsGetSamlpeStatResponseLibrary.h"

#include "CoreMinimal.h"


FString ULiveOpsDemoMsGetSamlpeStatResponseLibrary::LiveOpsDemoMsGetSamlpeStatResponseToJsonString(const ULiveOpsDemoMsGetSamlpeStatResponse* Serializable, const bool Pretty)
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

ULiveOpsDemoMsGetSamlpeStatResponse* ULiveOpsDemoMsGetSamlpeStatResponseLibrary::Make(int32 Value, UObject* Outer)
{
	auto Serializable = NewObject<ULiveOpsDemoMsGetSamlpeStatResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void ULiveOpsDemoMsGetSamlpeStatResponseLibrary::Break(const ULiveOpsDemoMsGetSamlpeStatResponse* Serializable, int32& Value)
{
	Value = Serializable->Value;
		
}

