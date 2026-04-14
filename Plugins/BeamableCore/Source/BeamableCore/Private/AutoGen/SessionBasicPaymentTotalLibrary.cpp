
#include "BeamableCore/Public/AutoGen/SessionBasicPaymentTotalLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionBasicPaymentTotalLibrary::SessionBasicPaymentTotalToJsonString(const USessionBasicPaymentTotal* Serializable, const bool Pretty)
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

USessionBasicPaymentTotal* USessionBasicPaymentTotalLibrary::Make(int64 TotalRevenue, FOptionalString CurrencyCode, UObject* Outer)
{
	auto Serializable = NewObject<USessionBasicPaymentTotal>(Outer);
	Serializable->TotalRevenue = TotalRevenue;
	Serializable->CurrencyCode = CurrencyCode;
	
	return Serializable;
}

void USessionBasicPaymentTotalLibrary::Break(const USessionBasicPaymentTotal* Serializable, int64& TotalRevenue, FOptionalString& CurrencyCode)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TotalRevenue = Serializable->TotalRevenue;
		CurrencyCode = Serializable->CurrencyCode;
	}
		
}

