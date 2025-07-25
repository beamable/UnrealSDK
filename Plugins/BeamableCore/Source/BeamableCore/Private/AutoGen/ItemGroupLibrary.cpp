
#include "BeamableCore/Public/AutoGen/ItemGroupLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemGroupLibrary::ItemGroupToJsonString(const UItemGroup* Serializable, const bool Pretty)
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

UItemGroup* UItemGroupLibrary::Make(FString Id, TArray<UItem*> Items, UObject* Outer)
{
	auto Serializable = NewObject<UItemGroup>(Outer);
	Serializable->Id = Id;
	Serializable->Items = Items;
	
	return Serializable;
}

void UItemGroupLibrary::Break(const UItemGroup* Serializable, FString& Id, TArray<UItem*>& Items)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Items = Serializable->Items;
	}
		
}

