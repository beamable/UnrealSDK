
#include "BeamableCore/Public/AutoGen/PurchaseRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPurchaseRequestBodyLibrary::PurchaseRequestBodyToJsonString(const UPurchaseRequestBody* Serializable, const bool Pretty)
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

UPurchaseRequestBody* UPurchaseRequestBodyLibrary::Make(FString PurchaseId, UObject* Outer)
{
	auto Serializable = NewObject<UPurchaseRequestBody>(Outer);
	Serializable->PurchaseId = PurchaseId;
	
	return Serializable;
}

void UPurchaseRequestBodyLibrary::Break(const UPurchaseRequestBody* Serializable, FString& PurchaseId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PurchaseId = Serializable->PurchaseId;
	}
		
}

