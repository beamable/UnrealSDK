
#include "BeamableCore/Public/AutoGen/LocalizedValueLibrary.h"

#include "CoreMinimal.h"


FString ULocalizedValueLibrary::LocalizedValueToJsonString(const ULocalizedValue* Serializable, const bool Pretty)
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

ULocalizedValue* ULocalizedValueLibrary::Make(FString Language, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<ULocalizedValue>(Outer);
	Serializable->Language = Language;
	Serializable->Value = Value;
	
	return Serializable;
}

void ULocalizedValueLibrary::Break(const ULocalizedValue* Serializable, FString& Language, FString& Value)
{
	Language = Serializable->Language;
	Value = Serializable->Value;
		
}

