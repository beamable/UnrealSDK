
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsPrepareNewPlayerResponseLibrary.h"

#include "CoreMinimal.h"


FString ULiveOpsDemoMsPrepareNewPlayerResponseLibrary::LiveOpsDemoMsPrepareNewPlayerResponseToJsonString(const ULiveOpsDemoMsPrepareNewPlayerResponse* Serializable, const bool Pretty)
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

ULiveOpsDemoMsPrepareNewPlayerResponse* ULiveOpsDemoMsPrepareNewPlayerResponseLibrary::Make(bool bValue, UObject* Outer)
{
	auto Serializable = NewObject<ULiveOpsDemoMsPrepareNewPlayerResponse>(Outer);
	Serializable->bValue = bValue;
	
	return Serializable;
}

void ULiveOpsDemoMsPrepareNewPlayerResponseLibrary::Break(const ULiveOpsDemoMsPrepareNewPlayerResponse* Serializable, bool& bValue)
{
	bValue = Serializable->bValue;
		
}

