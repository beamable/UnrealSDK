
#include "BeamableCore/Public/AutoGen/GetProductResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetProductResponseLibrary::GetProductResponseToJsonString(const UGetProductResponse* Serializable, const bool Pretty)
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

UGetProductResponse* UGetProductResponseLibrary::Make(FString Id, FString Name, FString Description, int32 Price, UObject* Outer)
{
	auto Serializable = NewObject<UGetProductResponse>(Outer);
	Serializable->Id = Id;
	Serializable->Name = Name;
	Serializable->Description = Description;
	Serializable->Price = Price;
	
	return Serializable;
}

void UGetProductResponseLibrary::Break(const UGetProductResponse* Serializable, FString& Id, FString& Name, FString& Description, int32& Price)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Name = Serializable->Name;
		Description = Serializable->Description;
		Price = Serializable->Price;
	}
		
}

