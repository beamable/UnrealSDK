
#include "BeamableCore/Public/AutoGen/GetCurrentManifestResponseLibrary.h"

#include "CoreMinimal.h"


FString UGetCurrentManifestResponseLibrary::GetCurrentManifestResponseToJsonString(const UGetCurrentManifestResponse* Serializable, const bool Pretty)
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

UGetCurrentManifestResponse* UGetCurrentManifestResponseLibrary::Make(UManifestView* Manifest, UObject* Outer)
{
	auto Serializable = NewObject<UGetCurrentManifestResponse>(Outer);
	Serializable->Manifest = Manifest;
	
	return Serializable;
}

void UGetCurrentManifestResponseLibrary::Break(const UGetCurrentManifestResponse* Serializable, UManifestView*& Manifest)
{
	Manifest = Serializable->Manifest;
		
}

