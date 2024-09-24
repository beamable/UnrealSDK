
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsIncrementStatResponseLibrary.h"

#include "CoreMinimal.h"


FString ULiveOpsDemoMsIncrementStatResponseLibrary::LiveOpsDemoMsIncrementStatResponseToJsonString(const ULiveOpsDemoMsIncrementStatResponse* Serializable, const bool Pretty)
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

ULiveOpsDemoMsIncrementStatResponse* ULiveOpsDemoMsIncrementStatResponseLibrary::Make(bool bValue, UObject* Outer)
{
	auto Serializable = NewObject<ULiveOpsDemoMsIncrementStatResponse>(Outer);
	Serializable->bValue = bValue;
	
	return Serializable;
}

void ULiveOpsDemoMsIncrementStatResponseLibrary::Break(const ULiveOpsDemoMsIncrementStatResponse* Serializable, bool& bValue)
{
	bValue = Serializable->bValue;
		
}

