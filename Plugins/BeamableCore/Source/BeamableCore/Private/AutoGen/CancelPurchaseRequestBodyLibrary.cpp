
#include "BeamableCore/Public/AutoGen/CancelPurchaseRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCancelPurchaseRequestBodyLibrary::CancelPurchaseRequestBodyToJsonString(const UCancelPurchaseRequestBody* Serializable, const bool Pretty)
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

UCancelPurchaseRequestBody* UCancelPurchaseRequestBodyLibrary::Make(int64 Txid, UObject* Outer)
{
	auto Serializable = NewObject<UCancelPurchaseRequestBody>(Outer);
	Serializable->Txid = Txid;
	
	return Serializable;
}

void UCancelPurchaseRequestBodyLibrary::Break(const UCancelPurchaseRequestBody* Serializable, int64& Txid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Txid = Serializable->Txid;
	}
		
}

