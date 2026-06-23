
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterGroundItemRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URegisterGroundItemRequestArgsLibrary::RegisterGroundItemRequestArgsToJsonString(const URegisterGroundItemRequestArgs* Serializable, const bool Pretty)
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

URegisterGroundItemRequestArgs* URegisterGroundItemRequestArgsLibrary::Make(FString GroundItemId, FString ContentId, int32 Quantity, FString ItemType, float PosX, float PosY, float PosZ, FString SpawnerId, UObject* Outer)
{
	auto Serializable = NewObject<URegisterGroundItemRequestArgs>(Outer);
	Serializable->GroundItemId = GroundItemId;
	Serializable->ContentId = ContentId;
	Serializable->Quantity = Quantity;
	Serializable->ItemType = ItemType;
	Serializable->PosX = PosX;
	Serializable->PosY = PosY;
	Serializable->PosZ = PosZ;
	Serializable->SpawnerId = SpawnerId;
	
	return Serializable;
}

void URegisterGroundItemRequestArgsLibrary::Break(const URegisterGroundItemRequestArgs* Serializable, FString& GroundItemId, FString& ContentId, int32& Quantity, FString& ItemType, float& PosX, float& PosY, float& PosZ, FString& SpawnerId)
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
		SpawnerId = Serializable->SpawnerId;
	}
		
}

