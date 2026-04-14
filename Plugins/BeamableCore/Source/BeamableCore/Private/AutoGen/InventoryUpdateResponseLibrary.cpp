
#include "BeamableCore/Public/AutoGen/InventoryUpdateResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInventoryUpdateResponseLibrary::InventoryUpdateResponseToJsonString(const UInventoryUpdateResponse* Serializable, const bool Pretty)
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

UInventoryUpdateResponse* UInventoryUpdateResponseLibrary::Make(FString Result, TMap<FString, FString> Data, FOptionalInventoryUpdateDelta Deltas, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryUpdateResponse>(Outer);
	Serializable->Result = Result;
	Serializable->Data = Data;
	Serializable->Deltas = Deltas;
	
	return Serializable;
}

void UInventoryUpdateResponseLibrary::Break(const UInventoryUpdateResponse* Serializable, FString& Result, TMap<FString, FString>& Data, FOptionalInventoryUpdateDelta& Deltas)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
		Data = Serializable->Data;
		Deltas = Serializable->Deltas;
	}
		
}

