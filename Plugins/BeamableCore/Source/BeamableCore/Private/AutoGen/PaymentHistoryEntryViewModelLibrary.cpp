
#include "BeamableCore/Public/AutoGen/PaymentHistoryEntryViewModelLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPaymentHistoryEntryViewModelLibrary::PaymentHistoryEntryViewModelToJsonString(const UPaymentHistoryEntryViewModel* Serializable, const bool Pretty)
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

UPaymentHistoryEntryViewModel* UPaymentHistoryEntryViewModelLibrary::Make(FString Change, FOptionalString Data, FOptionalString Timestamp, UObject* Outer)
{
	auto Serializable = NewObject<UPaymentHistoryEntryViewModel>(Outer);
	Serializable->Change = Change;
	Serializable->Data = Data;
	Serializable->Timestamp = Timestamp;
	
	return Serializable;
}

void UPaymentHistoryEntryViewModelLibrary::Break(const UPaymentHistoryEntryViewModel* Serializable, FString& Change, FOptionalString& Data, FOptionalString& Timestamp)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Change = Serializable->Change;
		Data = Serializable->Data;
		Timestamp = Serializable->Timestamp;
	}
		
}

