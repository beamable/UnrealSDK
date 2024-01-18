
#include "BeamableCore/Public/AutoGen/BeginPurchaseRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UBeginPurchaseRequestBodyLibrary::BeginPurchaseRequestBodyToJsonString(const UBeginPurchaseRequestBody* Serializable, const bool Pretty)
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

UBeginPurchaseRequestBody* UBeginPurchaseRequestBodyLibrary::Make(FString PurchaseId, FOptionalString Language, FOptionalString Time, UObject* Outer)
{
	auto Serializable = NewObject<UBeginPurchaseRequestBody>(Outer);
	Serializable->PurchaseId = PurchaseId;
	Serializable->Language = Language;
	Serializable->Time = Time;
	
	return Serializable;
}

void UBeginPurchaseRequestBodyLibrary::Break(const UBeginPurchaseRequestBody* Serializable, FString& PurchaseId, FOptionalString& Language, FOptionalString& Time)
{
	PurchaseId = Serializable->PurchaseId;
	Language = Serializable->Language;
	Time = Serializable->Time;
		
}

