
#include "BeamableCore/Public/AutoGen/StatUpdateRequestStringListFormatLibrary.h"

#include "CoreMinimal.h"


FString UStatUpdateRequestStringListFormatLibrary::StatUpdateRequestStringListFormatToJsonString(const UStatUpdateRequestStringListFormat* Serializable, const bool Pretty)
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

UStatUpdateRequestStringListFormat* UStatUpdateRequestStringListFormatLibrary::Make(FOptionalArrayOfStatStringListEntry Set, UObject* Outer)
{
	auto Serializable = NewObject<UStatUpdateRequestStringListFormat>(Outer);
	Serializable->Set = Set;
	
	return Serializable;
}

void UStatUpdateRequestStringListFormatLibrary::Break(const UStatUpdateRequestStringListFormat* Serializable, FOptionalArrayOfStatStringListEntry& Set)
{
	Set = Serializable->Set;
		
}

