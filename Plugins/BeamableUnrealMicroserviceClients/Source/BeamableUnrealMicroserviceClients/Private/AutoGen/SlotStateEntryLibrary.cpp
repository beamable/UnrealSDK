
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SlotStateEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USlotStateEntryLibrary::SlotStateEntryToJsonString(const USlotStateEntry* Serializable, const bool Pretty)
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

USlotStateEntry* USlotStateEntryLibrary::Make(FString SlotId, FString SeedId, FString HarvestId, int64 PlantedAt, int32 GrowSecs, UObject* Outer)
{
	auto Serializable = NewObject<USlotStateEntry>(Outer);
	Serializable->SlotId = SlotId;
	Serializable->SeedId = SeedId;
	Serializable->HarvestId = HarvestId;
	Serializable->PlantedAt = PlantedAt;
	Serializable->GrowSecs = GrowSecs;
	
	return Serializable;
}

void USlotStateEntryLibrary::Break(const USlotStateEntry* Serializable, FString& SlotId, FString& SeedId, FString& HarvestId, int64& PlantedAt, int32& GrowSecs)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SlotId = Serializable->SlotId;
		SeedId = Serializable->SeedId;
		HarvestId = Serializable->HarvestId;
		PlantedAt = Serializable->PlantedAt;
		GrowSecs = Serializable->GrowSecs;
	}
		
}

