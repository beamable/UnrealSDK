
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSUpgradeItemResponseLibrary.h"

#include "CoreMinimal.h"


FString ULiveOpsDemoMSUpgradeItemResponseLibrary::LiveOpsDemoMSUpgradeItemResponseToJsonString(const ULiveOpsDemoMSUpgradeItemResponse* Serializable, const bool Pretty)
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

ULiveOpsDemoMSUpgradeItemResponse* ULiveOpsDemoMSUpgradeItemResponseLibrary::Make(bool bValue, UObject* Outer)
{
	auto Serializable = NewObject<ULiveOpsDemoMSUpgradeItemResponse>(Outer);
	Serializable->bValue = bValue;
	
	return Serializable;
}

void ULiveOpsDemoMSUpgradeItemResponseLibrary::Break(const ULiveOpsDemoMSUpgradeItemResponse* Serializable, bool& bValue)
{
	bValue = Serializable->bValue;
		
}

