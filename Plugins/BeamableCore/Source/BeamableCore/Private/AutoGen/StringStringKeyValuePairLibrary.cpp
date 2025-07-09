
#include "BeamableCore/Public/AutoGen/StringStringKeyValuePairLibrary.h"

#include "CoreMinimal.h"


FString UStringStringKeyValuePairLibrary::StringStringKeyValuePairToJsonString(const UStringStringKeyValuePair* Serializable, const bool Pretty)
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

UStringStringKeyValuePair* UStringStringKeyValuePairLibrary::Make(FOptionalString Key, FOptionalString Value, UObject* Outer)
{
	auto Serializable = NewObject<UStringStringKeyValuePair>(Outer);
	Serializable->Key = Key;
	Serializable->Value = Value;
	
	return Serializable;
}

void UStringStringKeyValuePairLibrary::Break(const UStringStringKeyValuePair* Serializable, FOptionalString& Key, FOptionalString& Value)
{
	Key = Serializable->Key;
	Value = Serializable->Value;
		
}

