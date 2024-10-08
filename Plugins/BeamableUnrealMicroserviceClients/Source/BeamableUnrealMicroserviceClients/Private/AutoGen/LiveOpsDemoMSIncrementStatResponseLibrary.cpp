
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSIncrementStatResponseLibrary.h"

#include "CoreMinimal.h"


FString ULiveOpsDemoMSIncrementStatResponseLibrary::LiveOpsDemoMSIncrementStatResponseToJsonString(const ULiveOpsDemoMSIncrementStatResponse* Serializable, const bool Pretty)
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

ULiveOpsDemoMSIncrementStatResponse* ULiveOpsDemoMSIncrementStatResponseLibrary::Make(bool bValue, UObject* Outer)
{
	auto Serializable = NewObject<ULiveOpsDemoMSIncrementStatResponse>(Outer);
	Serializable->bValue = bValue;
	
	return Serializable;
}

void ULiveOpsDemoMSIncrementStatResponseLibrary::Break(const ULiveOpsDemoMSIncrementStatResponse* Serializable, bool& bValue)
{
	bValue = Serializable->bValue;
		
}

