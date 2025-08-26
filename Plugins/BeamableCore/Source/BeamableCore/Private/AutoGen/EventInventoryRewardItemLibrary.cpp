
#include "BeamableCore/Public/AutoGen/EventInventoryRewardItemLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventInventoryRewardItemLibrary::EventInventoryRewardItemToJsonString(const UEventInventoryRewardItem* Serializable, const bool Pretty)
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

UEventInventoryRewardItem* UEventInventoryRewardItemLibrary::Make(FString Id, FOptionalMapOfString Properties, UObject* Outer)
{
	auto Serializable = NewObject<UEventInventoryRewardItem>(Outer);
	Serializable->Id = Id;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UEventInventoryRewardItemLibrary::Break(const UEventInventoryRewardItem* Serializable, FString& Id, FOptionalMapOfString& Properties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Properties = Serializable->Properties;
	}
		
}

