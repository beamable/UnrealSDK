
#include "BeamableCore/Public/AutoGen/ItemDeltasLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemDeltasLibrary::ItemDeltasToJsonString(const UItemDeltas* Serializable, const bool Pretty)
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

UItemDeltas* UItemDeltasLibrary::Make(TArray<UItemPropertiesDelta*> Created, TArray<UItemPropertiesDelta*> Updated, TArray<UItemPropertiesDelta*> Deleted, UObject* Outer)
{
	auto Serializable = NewObject<UItemDeltas>(Outer);
	Serializable->Created = Created;
	Serializable->Updated = Updated;
	Serializable->Deleted = Deleted;
	
	return Serializable;
}

void UItemDeltasLibrary::Break(const UItemDeltas* Serializable, TArray<UItemPropertiesDelta*>& Created, TArray<UItemPropertiesDelta*>& Updated, TArray<UItemPropertiesDelta*>& Deleted)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Created = Serializable->Created;
		Updated = Serializable->Updated;
		Deleted = Serializable->Deleted;
	}
		
}

