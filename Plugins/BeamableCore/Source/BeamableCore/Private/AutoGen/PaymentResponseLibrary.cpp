
#include "BeamableCore/Public/AutoGen/PaymentResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPaymentResponseLibrary::PaymentResponseToJsonString(const UPaymentResponse* Serializable, const bool Pretty)
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

UPaymentResponse* UPaymentResponseLibrary::Make(FOptionalInt64 TransactionId, UObject* Outer)
{
	auto Serializable = NewObject<UPaymentResponse>(Outer);
	Serializable->TransactionId = TransactionId;
	
	return Serializable;
}

void UPaymentResponseLibrary::Break(const UPaymentResponse* Serializable, FOptionalInt64& TransactionId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TransactionId = Serializable->TransactionId;
	}
		
}

