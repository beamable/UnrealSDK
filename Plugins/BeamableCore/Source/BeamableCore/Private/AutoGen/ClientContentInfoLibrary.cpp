
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

UClientContentInfo* UClientContentInfoLibrary::Make(FString Uri, FString Version, FBeamContentId ContentId, EBeamContentType Type, TArray<FString> Tags, FOptionalInt64 UpdatedAt, FOptionalString Checksum, FOptionalInt64 CreatedAt, UObject* Outer)
{
	auto Serializable = NewObject<UClientContentInfo>(Outer);
	Serializable->Uri = Uri;
	Serializable->Version = Version;
	Serializable->ContentId = ContentId;
	Serializable->Type = Type;
	Serializable->Tags = Tags;
	Serializable->UpdatedAt = UpdatedAt;
	Serializable->Checksum = Checksum;
	Serializable->CreatedAt = CreatedAt;
	
	return Serializable;
}

void UClientContentInfoLibrary::Break(const UClientContentInfo* Serializable, FString& Uri, FString& Version, FBeamContentId& ContentId, EBeamContentType& Type, TArray<FString>& Tags, FOptionalInt64& UpdatedAt, FOptionalString& Checksum, FOptionalInt64& CreatedAt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Uri = Serializable->Uri;
		Version = Serializable->Version;
		ContentId = Serializable->ContentId;
		Type = Serializable->Type;
		Tags = Serializable->Tags;
		UpdatedAt = Serializable->UpdatedAt;
		Checksum = Serializable->Checksum;
		CreatedAt = Serializable->CreatedAt;
	}
		
}

