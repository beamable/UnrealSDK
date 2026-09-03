
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectHarvestRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCollectHarvestRequestArgsLibrary::CollectHarvestRequestArgsToJsonString(const UCollectHarvestRequestArgs* Serializable, const bool Pretty)
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

UCollectHarvestRequestArgs* UCollectHarvestRequestArgsLibrary::Make(FString SlotId, UObject* Outer)
{
	auto Serializable = NewObject<UCollectHarvestRequestArgs>(Outer);
	Serializable->SlotId = SlotId;
	
	return Serializable;
}

void UCollectHarvestRequestArgsLibrary::Break(const UCollectHarvestRequestArgs* Serializable, FString& SlotId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SlotId = Serializable->SlotId;
	}
		
}

