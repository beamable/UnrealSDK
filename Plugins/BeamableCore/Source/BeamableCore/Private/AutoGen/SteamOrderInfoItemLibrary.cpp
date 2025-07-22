
#include "BeamableCore/Public/AutoGen/SteamOrderInfoItemLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USteamOrderInfoItemLibrary::SteamOrderInfoItemToJsonString(const USteamOrderInfoItem* Serializable, const bool Pretty)
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

USteamOrderInfoItem* USteamOrderInfoItemLibrary::Make(int64 Vat, int64 Amount, int64 Itemid, int64 Qty, FString Itemstatus, UObject* Outer)
{
	auto Serializable = NewObject<USteamOrderInfoItem>(Outer);
	Serializable->Vat = Vat;
	Serializable->Amount = Amount;
	Serializable->Itemid = Itemid;
	Serializable->Qty = Qty;
	Serializable->Itemstatus = Itemstatus;
	
	return Serializable;
}

void USteamOrderInfoItemLibrary::Break(const USteamOrderInfoItem* Serializable, int64& Vat, int64& Amount, int64& Itemid, int64& Qty, FString& Itemstatus)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Vat = Serializable->Vat;
		Amount = Serializable->Amount;
		Itemid = Serializable->Itemid;
		Qty = Serializable->Qty;
		Itemstatus = Serializable->Itemstatus;
	}
		
}

