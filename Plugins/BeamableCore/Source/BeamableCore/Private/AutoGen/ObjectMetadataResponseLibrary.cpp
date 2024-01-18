
#include "BeamableCore/Public/AutoGen/ObjectMetadataResponseLibrary.h"

#include "CoreMinimal.h"


FString UObjectMetadataResponseLibrary::ObjectMetadataResponseToJsonString(const UObjectMetadataResponse* Serializable, const bool Pretty)
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

UObjectMetadataResponse* UObjectMetadataResponseLibrary::Make(FString ObjectKey, TMap<FString, FString> Metadata, UObject* Outer)
{
	auto Serializable = NewObject<UObjectMetadataResponse>(Outer);
	Serializable->ObjectKey = ObjectKey;
	Serializable->Metadata = Metadata;
	
	return Serializable;
}

void UObjectMetadataResponseLibrary::Break(const UObjectMetadataResponse* Serializable, FString& ObjectKey, TMap<FString, FString>& Metadata)
{
	ObjectKey = Serializable->ObjectKey;
	Metadata = Serializable->Metadata;
		
}

