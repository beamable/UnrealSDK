
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeginPurchaseResponseLibrary::BeginPurchaseResponseToJsonString(const UBeginPurchaseResponse* Serializable, const bool Pretty)
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

UBeginPurchaseResponse* UBeginPurchaseResponseLibrary::Make(int64 Txid, FOptionalString AccessToken, UObject* Outer)
{
	auto Serializable = NewObject<UBeginPurchaseResponse>(Outer);
	Serializable->Txid = Txid;
	Serializable->AccessToken = AccessToken;
	
	return Serializable;
}

void UBeginPurchaseResponseLibrary::Break(const UBeginPurchaseResponse* Serializable, int64& Txid, FOptionalString& AccessToken)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Txid = Serializable->Txid;
		AccessToken = Serializable->AccessToken;
	}
		
}

