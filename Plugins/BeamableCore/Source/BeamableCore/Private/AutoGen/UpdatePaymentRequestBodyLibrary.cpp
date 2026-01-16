
#include "BeamableCore/Public/AutoGen/UpdatePaymentRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdatePaymentRequestBodyLibrary::UpdatePaymentRequestBodyToJsonString(const UUpdatePaymentRequestBody* Serializable, const bool Pretty)
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

UUpdatePaymentRequestBody* UUpdatePaymentRequestBodyLibrary::Make(EBeamTransactionState State, FOptionalString Reason, UObject* Outer)
{
	auto Serializable = NewObject<UUpdatePaymentRequestBody>(Outer);
	Serializable->State = State;
	Serializable->Reason = Reason;
	
	return Serializable;
}

void UUpdatePaymentRequestBodyLibrary::Break(const UUpdatePaymentRequestBody* Serializable, EBeamTransactionState& State, FOptionalString& Reason)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		State = Serializable->State;
		Reason = Serializable->Reason;
	}
		
}

