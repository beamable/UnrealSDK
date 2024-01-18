
#include "BeamableCore/Public/AutoGen/TextDefinitionLibrary.h"

#include "CoreMinimal.h"


FString UTextDefinitionLibrary::TextDefinitionToJsonString(const UTextDefinition* Serializable, const bool Pretty)
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

UTextDefinition* UTextDefinitionLibrary::Make(FBeamContentId Id, FString Checksum, TMap<FString, FString> Properties, FOptionalArrayOfString Tags, UObject* Outer)
{
	auto Serializable = NewObject<UTextDefinition>(Outer);
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->Properties = Properties;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UTextDefinitionLibrary::Break(const UTextDefinition* Serializable, FBeamContentId& Id, FString& Checksum, TMap<FString, FString>& Properties, FOptionalArrayOfString& Tags)
{
	Id = Serializable->Id;
	Checksum = Serializable->Checksum;
	Properties = Serializable->Properties;
	Tags = Serializable->Tags;
		
}

