
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GroundItemEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroundItemEntryLibrary::GroundItemEntryToJsonString(const UGroundItemEntry* Serializable, const bool Pretty)
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

UGroundItemEntry* UGroundItemEntryLibrary::Make(FString GroundItemId, FString ContentId, int32 Quantity, FString ItemType, float PosX, float PosY, float PosZ, UObject* Outer)
{
	auto Serializable = NewObject<UGroundItemEntry>(Outer);
	Serializable->GroundItemId = GroundItemId;
	Serializable->ContentId = ContentId;
	Serializable->Quantity = Quantity;
	Serializable->ItemType = ItemType;
	Serializable->PosX = PosX;
	Serializable->PosY = PosY;
	Serializable->PosZ = PosZ;
	
	return Serializable;
}

void UGroundItemEntryLibrary::Break(const UGroundItemEntry* Serializable, FString& GroundItemId, FString& ContentId, int32& Quantity, FString& ItemType, float& PosX, float& PosY, float& PosZ)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GroundItemId = Serializable->GroundItemId;
		ContentId = Serializable->ContentId;
		Quantity = Serializable->Quantity;
		ItemType = Serializable->ItemType;
		PosX = Serializable->PosX;
		PosY = Serializable->PosY;
		PosZ = Serializable->PosZ;
	}
		
}

