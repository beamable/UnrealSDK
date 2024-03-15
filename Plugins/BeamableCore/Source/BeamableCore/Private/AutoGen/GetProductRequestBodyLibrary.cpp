
#include "BeamableCore/Public/AutoGen/GetProductRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UGetProductRequestBodyLibrary::GetProductRequestBodyToJsonString(const UGetProductRequestBody* Serializable, const bool Pretty)
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

UGetProductRequestBody* UGetProductRequestBodyLibrary::Make(FString Sku, UObject* Outer)
{
	auto Serializable = NewObject<UGetProductRequestBody>(Outer);
	Serializable->Sku = Sku;
	
	return Serializable;
}

void UGetProductRequestBodyLibrary::Break(const UGetProductRequestBody* Serializable, FString& Sku)
{
	Sku = Serializable->Sku;
		
}

