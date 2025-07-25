
#include "BeamableCore/Public/AutoGen/SteamOrderInfoResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USteamOrderInfoResponseLibrary::SteamOrderInfoResponseToJsonString(const USteamOrderInfoResponse* Serializable, const bool Pretty)
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

USteamOrderInfoResponse* USteamOrderInfoResponseLibrary::Make(FString Usstate, FString Country, FString Timecreated, int64 Transid, FString Status, int64 Orderid, int64 Steamid, FString Currency, FString Time, TArray<USteamOrderInfoItem*> Items, UObject* Outer)
{
	auto Serializable = NewObject<USteamOrderInfoResponse>(Outer);
	Serializable->Usstate = Usstate;
	Serializable->Country = Country;
	Serializable->Timecreated = Timecreated;
	Serializable->Transid = Transid;
	Serializable->Status = Status;
	Serializable->Orderid = Orderid;
	Serializable->Steamid = Steamid;
	Serializable->Currency = Currency;
	Serializable->Time = Time;
	Serializable->Items = Items;
	
	return Serializable;
}

void USteamOrderInfoResponseLibrary::Break(const USteamOrderInfoResponse* Serializable, FString& Usstate, FString& Country, FString& Timecreated, int64& Transid, FString& Status, int64& Orderid, int64& Steamid, FString& Currency, FString& Time, TArray<USteamOrderInfoItem*>& Items)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Usstate = Serializable->Usstate;
		Country = Serializable->Country;
		Timecreated = Serializable->Timecreated;
		Transid = Serializable->Transid;
		Status = Serializable->Status;
		Orderid = Serializable->Orderid;
		Steamid = Serializable->Steamid;
		Currency = Serializable->Currency;
		Time = Serializable->Time;
		Items = Serializable->Items;
	}
		
}

