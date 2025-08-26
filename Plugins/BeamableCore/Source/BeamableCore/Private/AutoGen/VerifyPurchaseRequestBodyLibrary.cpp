
#include "BeamableCore/Public/AutoGen/VerifyPurchaseRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UVerifyPurchaseRequestBodyLibrary::VerifyPurchaseRequestBodyToJsonString(const UVerifyPurchaseRequestBody* Serializable, const bool Pretty)
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

UVerifyPurchaseRequestBody* UVerifyPurchaseRequestBodyLibrary::Make(FString Receipt, UObject* Outer)
{
	auto Serializable = NewObject<UVerifyPurchaseRequestBody>(Outer);
	Serializable->Receipt = Receipt;
	
	return Serializable;
}

void UVerifyPurchaseRequestBodyLibrary::Break(const UVerifyPurchaseRequestBody* Serializable, FString& Receipt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Receipt = Serializable->Receipt;
	}
		
}

