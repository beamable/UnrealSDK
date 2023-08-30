
#include "BeamableCore/Public/AutoGen/TagLibrary.h"

#include "CoreMinimal.h"


FString UTagLibrary::TagToJsonString(const UTag* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UTag* UTagLibrary::Make(FOptionalString Name, FOptionalString Value, UObject* Outer)
{
	auto Serializable = NewObject<UTag>(Outer);
	Serializable->Name = Name;
	Serializable->Value = Value;
	
	return Serializable;
}

void UTagLibrary::Break(const UTag* Serializable, FOptionalString& Name, FOptionalString& Value)
{
	Name = Serializable->Name;
	Value = Serializable->Value;
		
}

