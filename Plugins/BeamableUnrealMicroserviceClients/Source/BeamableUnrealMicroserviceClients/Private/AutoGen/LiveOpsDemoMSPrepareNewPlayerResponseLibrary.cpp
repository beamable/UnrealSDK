
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSPrepareNewPlayerResponseLibrary.h"

#include "CoreMinimal.h"


FString ULiveOpsDemoMSPrepareNewPlayerResponseLibrary::LiveOpsDemoMSPrepareNewPlayerResponseToJsonString(const ULiveOpsDemoMSPrepareNewPlayerResponse* Serializable, const bool Pretty)
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

ULiveOpsDemoMSPrepareNewPlayerResponse* ULiveOpsDemoMSPrepareNewPlayerResponseLibrary::Make(bool bValue, UObject* Outer)
{
	auto Serializable = NewObject<ULiveOpsDemoMSPrepareNewPlayerResponse>(Outer);
	Serializable->bValue = bValue;
	
	return Serializable;
}

void ULiveOpsDemoMSPrepareNewPlayerResponseLibrary::Break(const ULiveOpsDemoMSPrepareNewPlayerResponse* Serializable, bool& bValue)
{
	bValue = Serializable->bValue;
		
}

