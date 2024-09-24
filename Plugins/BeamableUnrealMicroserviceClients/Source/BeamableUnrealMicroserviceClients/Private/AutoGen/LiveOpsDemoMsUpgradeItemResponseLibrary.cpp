
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsUpgradeItemResponseLibrary.h"

#include "CoreMinimal.h"


FString ULiveOpsDemoMsUpgradeItemResponseLibrary::LiveOpsDemoMsUpgradeItemResponseToJsonString(const ULiveOpsDemoMsUpgradeItemResponse* Serializable, const bool Pretty)
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

ULiveOpsDemoMsUpgradeItemResponse* ULiveOpsDemoMsUpgradeItemResponseLibrary::Make(bool bValue, UObject* Outer)
{
	auto Serializable = NewObject<ULiveOpsDemoMsUpgradeItemResponse>(Outer);
	Serializable->bValue = bValue;
	
	return Serializable;
}

void ULiveOpsDemoMsUpgradeItemResponseLibrary::Break(const ULiveOpsDemoMsUpgradeItemResponse* Serializable, bool& bValue)
{
	bValue = Serializable->bValue;
		
}

