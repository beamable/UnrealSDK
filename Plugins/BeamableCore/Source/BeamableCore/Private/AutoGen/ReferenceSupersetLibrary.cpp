
#include "BeamableCore/Public/AutoGen/ReferenceSupersetLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UReferenceSupersetLibrary::ReferenceSupersetToJsonString(const UReferenceSuperset* Serializable, const bool Pretty)
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

UReferenceSuperset* UReferenceSupersetLibrary::Make(FString Uri, FString Version, FBeamContentId Id, FString Type, FOptionalString Checksum, FOptionalString Visibility, FOptionalArrayOfString Tags, UObject* Outer)
{
	auto Serializable = NewObject<UReferenceSuperset>(Outer);
	Serializable->Uri = Uri;
	Serializable->Version = Version;
	Serializable->Id = Id;
	Serializable->Type = Type;
	Serializable->Checksum = Checksum;
	Serializable->Visibility = Visibility;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UReferenceSupersetLibrary::Break(const UReferenceSuperset* Serializable, FString& Uri, FString& Version, FBeamContentId& Id, FString& Type, FOptionalString& Checksum, FOptionalString& Visibility, FOptionalArrayOfString& Tags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Uri = Serializable->Uri;
		Version = Serializable->Version;
		Id = Serializable->Id;
		Type = Serializable->Type;
		Checksum = Serializable->Checksum;
		Visibility = Serializable->Visibility;
		Tags = Serializable->Tags;
	}
		
}

