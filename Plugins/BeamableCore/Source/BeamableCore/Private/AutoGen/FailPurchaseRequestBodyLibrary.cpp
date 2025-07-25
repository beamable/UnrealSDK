
#include "BeamableCore/Public/AutoGen/FailPurchaseRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UFailPurchaseRequestBodyLibrary::FailPurchaseRequestBodyToJsonString(const UFailPurchaseRequestBody* Serializable, const bool Pretty)
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

UFailPurchaseRequestBody* UFailPurchaseRequestBodyLibrary::Make(int64 Txid, FString Reason, UObject* Outer)
{
	auto Serializable = NewObject<UFailPurchaseRequestBody>(Outer);
	Serializable->Txid = Txid;
	Serializable->Reason = Reason;
	
	return Serializable;
}

void UFailPurchaseRequestBodyLibrary::Break(const UFailPurchaseRequestBody* Serializable, int64& Txid, FString& Reason)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Txid = Serializable->Txid;
		Reason = Serializable->Reason;
	}
		
}

