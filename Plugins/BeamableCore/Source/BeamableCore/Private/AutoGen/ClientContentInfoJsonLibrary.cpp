
#include "BeamableCore/Public/AutoGen/ClientContentInfoJsonLibrary.h"

#include "CoreMinimal.h"


FString UClientContentInfoJsonLibrary::ClientContentInfoJsonToJsonString(const UClientContentInfoJson* Serializable, const bool Pretty)
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

UClientContentInfoJson* UClientContentInfoJsonLibrary::Make(FString Uri, FString Version, FBeamContentId ContentId, EContentType Type, TArray<FString> Tags, UObject* Outer)
{
	auto Serializable = NewObject<UClientContentInfoJson>(Outer);
	Serializable->Uri = Uri;
	Serializable->Version = Version;
	Serializable->ContentId = ContentId;
	Serializable->Type = Type;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UClientContentInfoJsonLibrary::Break(const UClientContentInfoJson* Serializable, FString& Uri, FString& Version, FBeamContentId& ContentId, EContentType& Type, TArray<FString>& Tags)
{
	Uri = Serializable->Uri;
	Version = Serializable->Version;
	ContentId = Serializable->ContentId;
	Type = Serializable->Type;
	Tags = Serializable->Tags;
		
}

