
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PlantSeedRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlantSeedRequestArgsLibrary::PlantSeedRequestArgsToJsonString(const UPlantSeedRequestArgs* Serializable, const bool Pretty)
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

UPlantSeedRequestArgs* UPlantSeedRequestArgsLibrary::Make(FString SeedContentId, FString SlotId, UObject* Outer)
{
	auto Serializable = NewObject<UPlantSeedRequestArgs>(Outer);
	Serializable->SeedContentId = SeedContentId;
	Serializable->SlotId = SlotId;
	
	return Serializable;
}

void UPlantSeedRequestArgsLibrary::Break(const UPlantSeedRequestArgs* Serializable, FString& SeedContentId, FString& SlotId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SeedContentId = Serializable->SeedContentId;
		SlotId = Serializable->SlotId;
	}
		
}

