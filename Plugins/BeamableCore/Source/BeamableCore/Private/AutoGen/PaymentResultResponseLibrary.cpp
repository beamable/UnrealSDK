
#include "BeamableCore/Public/AutoGen/PaymentResultResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPaymentResultResponseLibrary::PaymentResultResponseToJsonString(const UPaymentResultResponse* Serializable, const bool Pretty)
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

UPaymentResultResponse* UPaymentResultResponseLibrary::Make(FString Result, UObject* Outer)
{
	auto Serializable = NewObject<UPaymentResultResponse>(Outer);
	Serializable->Result = Result;
	
	return Serializable;
}

void UPaymentResultResponseLibrary::Break(const UPaymentResultResponse* Serializable, FString& Result)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
	}
		
}

