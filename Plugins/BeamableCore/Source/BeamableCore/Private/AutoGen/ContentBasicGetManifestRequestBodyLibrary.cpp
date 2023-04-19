
#include "BeamableCore/Public/AutoGen/ContentBasicGetManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UContentBasicGetManifestRequestBodyLibrary::ContentBasicGetManifestRequestBodyToJsonString(const UContentBasicGetManifestRequestBody* Serializable, const bool Pretty)
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

UContentBasicGetManifestRequestBody* UContentBasicGetManifestRequestBodyLibrary::Make(FOptionalBeamContentManifestId Id, UObject* Outer)
{
	auto Serializable = NewObject<UContentBasicGetManifestRequestBody>(Outer);
	Serializable->Id = Id;
	
	return Serializable;
}

void UContentBasicGetManifestRequestBodyLibrary::Break(const UContentBasicGetManifestRequestBody* Serializable, FOptionalBeamContentManifestId& Id)
{
	Id = Serializable->Id;
		
}

