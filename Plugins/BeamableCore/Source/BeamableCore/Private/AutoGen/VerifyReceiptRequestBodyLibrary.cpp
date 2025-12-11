
#include "BeamableCore/Public/AutoGen/VerifyReceiptRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UVerifyReceiptRequestBodyLibrary::VerifyReceiptRequestBodyToJsonString(const UVerifyReceiptRequestBody* Serializable, const bool Pretty)
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

UVerifyReceiptRequestBody* UVerifyReceiptRequestBodyLibrary::Make(FOptionalString Provider, FOptionalString Receipt, UObject* Outer)
{
	auto Serializable = NewObject<UVerifyReceiptRequestBody>(Outer);
	Serializable->Provider = Provider;
	Serializable->Receipt = Receipt;
	
	return Serializable;
}

void UVerifyReceiptRequestBodyLibrary::Break(const UVerifyReceiptRequestBody* Serializable, FOptionalString& Provider, FOptionalString& Receipt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Provider = Serializable->Provider;
		Receipt = Serializable->Receipt;
	}
		
}

