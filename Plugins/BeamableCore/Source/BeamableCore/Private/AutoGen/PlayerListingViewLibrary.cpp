
#include "BeamableCore/Public/AutoGen/PlayerListingViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerListingViewLibrary::PlayerListingViewToJsonString(const UPlayerListingView* Serializable, const bool Pretty)
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

UPlayerListingView* UPlayerListingViewLibrary::Make(bool bActive, bool bQueryAfterPurchase, FString Symbol, int64 SecondsActive, UPlayerOfferView* Offer, TArray<UClientDataEntry*> ClientDataList, TMap<FString, FString> ClientData, FOptionalInt32 Cooldown, FOptionalInt32 PurchasesRemain, FOptionalInt64 SecondsRemain, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerListingView>(Outer);
	Serializable->bActive = bActive;
	Serializable->bQueryAfterPurchase = bQueryAfterPurchase;
	Serializable->Symbol = Symbol;
	Serializable->SecondsActive = SecondsActive;
	Serializable->Offer = Offer;
	Serializable->ClientDataList = ClientDataList;
	Serializable->ClientData = ClientData;
	Serializable->Cooldown = Cooldown;
	Serializable->PurchasesRemain = PurchasesRemain;
	Serializable->SecondsRemain = SecondsRemain;
	
	return Serializable;
}

void UPlayerListingViewLibrary::Break(const UPlayerListingView* Serializable, bool& bActive, bool& bQueryAfterPurchase, FString& Symbol, int64& SecondsActive, UPlayerOfferView*& Offer, TArray<UClientDataEntry*>& ClientDataList, TMap<FString, FString>& ClientData, FOptionalInt32& Cooldown, FOptionalInt32& PurchasesRemain, FOptionalInt64& SecondsRemain)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bActive = Serializable->bActive;
		bQueryAfterPurchase = Serializable->bQueryAfterPurchase;
		Symbol = Serializable->Symbol;
		SecondsActive = Serializable->SecondsActive;
		Offer = Serializable->Offer;
		ClientDataList = Serializable->ClientDataList;
		ClientData = Serializable->ClientData;
		Cooldown = Serializable->Cooldown;
		PurchasesRemain = Serializable->PurchasesRemain;
		SecondsRemain = Serializable->SecondsRemain;
	}
		
}

