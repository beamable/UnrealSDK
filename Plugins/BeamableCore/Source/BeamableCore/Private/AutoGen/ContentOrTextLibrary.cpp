
#include "BeamableCore/Public/AutoGen/ContentOrTextLibrary.h"

#include "CoreMinimal.h"


FString UContentOrTextLibrary::ContentOrTextToJsonString(const UContentOrText* Serializable, const bool Pretty)
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

UContentOrText* UContentOrTextLibrary::Make(FBeamContentId Id, FString Version, TMap<FString, FString> Properties, UObject* Outer)
{
	auto Serializable = NewObject<UContentOrText>(Outer);
	Serializable->Id = Id;
	Serializable->Version = Version;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UContentOrTextLibrary::Break(const UContentOrText* Serializable, FBeamContentId& Id, FString& Version, TMap<FString, FString>& Properties)
{
	Id = Serializable->Id;
	Version = Serializable->Version;
	Properties = Serializable->Properties;
		
}

