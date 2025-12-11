
#include "BeamableCore/Public/AutoGen/CompletePaymentRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCompletePaymentRequestBodyLibrary::CompletePaymentRequestBodyToJsonString(const UCompletePaymentRequestBody* Serializable, const bool Pretty)
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

UCompletePaymentRequestBody* UCompletePaymentRequestBodyLibrary::Make(FString PaymentProvider, FString Receipt, FString PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UCompletePaymentRequestBody>(Outer);
	Serializable->PaymentProvider = PaymentProvider;
	Serializable->Receipt = Receipt;
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UCompletePaymentRequestBodyLibrary::Break(const UCompletePaymentRequestBody* Serializable, FString& PaymentProvider, FString& Receipt, FString& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PaymentProvider = Serializable->PaymentProvider;
		Receipt = Serializable->Receipt;
		PlayerId = Serializable->PlayerId;
	}
		
}

