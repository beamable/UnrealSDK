
#include "BeamableCore/Public/AutoGen/EventInventoryPendingRewardsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventInventoryPendingRewardsLibrary::EventInventoryPendingRewardsToJsonString(const UEventInventoryPendingRewards* Serializable, const bool Pretty)
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

UEventInventoryPendingRewards* UEventInventoryPendingRewardsLibrary::Make(bool bEmpty, FOptionalArrayOfItemCreateRequestBody Items, FOptionalMapOfString Currencies, UObject* Outer)
{
	auto Serializable = NewObject<UEventInventoryPendingRewards>(Outer);
	Serializable->bEmpty = bEmpty;
	Serializable->Items = Items;
	Serializable->Currencies = Currencies;
	
	return Serializable;
}

void UEventInventoryPendingRewardsLibrary::Break(const UEventInventoryPendingRewards* Serializable, bool& bEmpty, FOptionalArrayOfItemCreateRequestBody& Items, FOptionalMapOfString& Currencies)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bEmpty = Serializable->bEmpty;
		Items = Serializable->Items;
		Currencies = Serializable->Currencies;
	}
		
}

