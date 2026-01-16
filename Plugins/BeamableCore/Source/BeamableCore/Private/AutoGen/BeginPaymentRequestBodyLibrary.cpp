
#include "BeamableCore/Public/AutoGen/BeginPaymentRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeginPaymentRequestBodyLibrary::BeginPaymentRequestBodyToJsonString(const UBeginPaymentRequestBody* Serializable, const bool Pretty)
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

UBeginPaymentRequestBody* UBeginPaymentRequestBodyLibrary::Make(FString PlayerId, FString PaymentProvider, UTransactionDetails* Details, FOptionalString InitHistoryData, UObject* Outer)
{
	auto Serializable = NewObject<UBeginPaymentRequestBody>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->PaymentProvider = PaymentProvider;
	Serializable->Details = Details;
	Serializable->InitHistoryData = InitHistoryData;
	
	return Serializable;
}

void UBeginPaymentRequestBodyLibrary::Break(const UBeginPaymentRequestBody* Serializable, FString& PlayerId, FString& PaymentProvider, UTransactionDetails*& Details, FOptionalString& InitHistoryData)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		PaymentProvider = Serializable->PaymentProvider;
		Details = Serializable->Details;
		InitHistoryData = Serializable->InitHistoryData;
	}
		
}

