
#include "BeamableCore/Public/AutoGen/ClientContentInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UClientContentInfoLibrary::ClientContentInfoToJsonString(const UClientContentInfo* Serializable, const bool Pretty)
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

UClientContentInfo* UClientContentInfoLibrary::Make(FString Uri, FString Version, FBeamContentId ContentId, EBeamContentType Type, TArray<FString> Tags, FOptionalString Checksum, UObject* Outer)
{
	auto Serializable = NewObject<UClientContentInfo>(Outer);
	Serializable->Uri = Uri;
	Serializable->Version = Version;
	Serializable->ContentId = ContentId;
	Serializable->Type = Type;
	Serializable->Tags = Tags;
	Serializable->Checksum = Checksum;
	
	return Serializable;
}

void UClientContentInfoLibrary::Break(const UClientContentInfo* Serializable, FString& Uri, FString& Version, FBeamContentId& ContentId, EBeamContentType& Type, TArray<FString>& Tags, FOptionalString& Checksum)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Uri = Serializable->Uri;
		Version = Serializable->Version;
		ContentId = Serializable->ContentId;
		Type = Serializable->Type;
		Tags = Serializable->Tags;
		Checksum = Serializable->Checksum;
	}
		
}

