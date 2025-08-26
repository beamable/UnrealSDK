
#include "BeamableCore/Public/AutoGen/UpdateCustomerRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdateCustomerRequestBodyLibrary::UpdateCustomerRequestBodyToJsonString(const UUpdateCustomerRequestBody* Serializable, const bool Pretty)
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

UUpdateCustomerRequestBody* UUpdateCustomerRequestBodyLibrary::Make(FOptionalPaymentStatus PaymentStatus, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateCustomerRequestBody>(Outer);
	Serializable->PaymentStatus = PaymentStatus;
	
	return Serializable;
}

void UUpdateCustomerRequestBodyLibrary::Break(const UUpdateCustomerRequestBody* Serializable, FOptionalPaymentStatus& PaymentStatus)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PaymentStatus = Serializable->PaymentStatus;
	}
		
}

