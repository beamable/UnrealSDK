
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSGetSampleStatResponseLibrary.h"

#include "CoreMinimal.h"


FString ULiveOpsDemoMSGetSampleStatResponseLibrary::LiveOpsDemoMSGetSampleStatResponseToJsonString(const ULiveOpsDemoMSGetSampleStatResponse* Serializable, const bool Pretty)
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

ULiveOpsDemoMSGetSampleStatResponse* ULiveOpsDemoMSGetSampleStatResponseLibrary::Make(int32 Value, UObject* Outer)
{
	auto Serializable = NewObject<ULiveOpsDemoMSGetSampleStatResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void ULiveOpsDemoMSGetSampleStatResponseLibrary::Break(const ULiveOpsDemoMSGetSampleStatResponse* Serializable, int32& Value)
{
	Value = Serializable->Value;
		
}

