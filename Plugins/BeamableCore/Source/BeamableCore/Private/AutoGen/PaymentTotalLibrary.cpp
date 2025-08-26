
#include "BeamableCore/Public/AutoGen/PaymentTotalLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPaymentTotalLibrary::PaymentTotalToJsonString(const UPaymentTotal* Serializable, const bool Pretty)
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

UPaymentTotal* UPaymentTotalLibrary::Make(int64 TotalRevenue, FOptionalString CurrencyCode, UObject* Outer)
{
	auto Serializable = NewObject<UPaymentTotal>(Outer);
	Serializable->TotalRevenue = TotalRevenue;
	Serializable->CurrencyCode = CurrencyCode;
	
	return Serializable;
}

void UPaymentTotalLibrary::Break(const UPaymentTotal* Serializable, int64& TotalRevenue, FOptionalString& CurrencyCode)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TotalRevenue = Serializable->TotalRevenue;
		CurrencyCode = Serializable->CurrencyCode;
	}
		
}

