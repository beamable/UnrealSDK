
#include "BeamableCore/Public/AutoGen/ContentDefinitionLibrary.h"

#include "CoreMinimal.h"


FString UContentDefinitionLibrary::ContentDefinitionToJsonString(const UContentDefinition* Serializable, const bool Pretty)
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

UContentDefinition* UContentDefinitionLibrary::Make(FString Prefix, FBeamContentId Id, FString Checksum, TMap<FString, UContentMeta*> Properties, FOptionalArrayOfString Tags, FOptionalArrayOfMapOfContentMeta Variants, UObject* Outer)
{
	auto Serializable = NewObject<UContentDefinition>(Outer);
	Serializable->Prefix = Prefix;
	Serializable->Id = Id;
	Serializable->Checksum = Checksum;
	Serializable->Properties = Properties;
	Serializable->Tags = Tags;
	Serializable->Variants = Variants;
	
	return Serializable;
}

void UContentDefinitionLibrary::Break(const UContentDefinition* Serializable, FString& Prefix, FBeamContentId& Id, FString& Checksum, TMap<FString, UContentMeta*>& Properties, FOptionalArrayOfString& Tags, FOptionalArrayOfMapOfContentMeta& Variants)
{
	Prefix = Serializable->Prefix;
	Id = Serializable->Id;
	Checksum = Serializable->Checksum;
	Properties = Serializable->Properties;
	Tags = Serializable->Tags;
	Variants = Serializable->Variants;
		
}

