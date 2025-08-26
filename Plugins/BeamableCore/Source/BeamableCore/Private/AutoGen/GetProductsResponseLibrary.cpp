
#include "BeamableCore/Public/AutoGen/GetProductsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetProductsResponseLibrary::GetProductsResponseToJsonString(const UGetProductsResponse* Serializable, const bool Pretty)
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

UGetProductsResponse* UGetProductsResponseLibrary::Make(TArray<UProductView*> Products, UObject* Outer)
{
	auto Serializable = NewObject<UGetProductsResponse>(Outer);
	Serializable->Products = Products;
	
	return Serializable;
}

void UGetProductsResponseLibrary::Break(const UGetProductsResponse* Serializable, TArray<UProductView*>& Products)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Products = Serializable->Products;
	}
		
}

