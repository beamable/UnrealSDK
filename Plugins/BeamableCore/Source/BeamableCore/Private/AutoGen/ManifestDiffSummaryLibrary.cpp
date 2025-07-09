
#include "BeamableCore/Public/AutoGen/ManifestDiffSummaryLibrary.h"

#include "CoreMinimal.h"


FString UManifestDiffSummaryLibrary::ManifestDiffSummaryToJsonString(const UManifestDiffSummary* Serializable, const bool Pretty)
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

UManifestDiffSummary* UManifestDiffSummaryLibrary::Make(FString ManifestUid, FString DiffUrl, int64 CreatedDate, UObject* Outer)
{
	auto Serializable = NewObject<UManifestDiffSummary>(Outer);
	Serializable->ManifestUid = ManifestUid;
	Serializable->DiffUrl = DiffUrl;
	Serializable->CreatedDate = CreatedDate;
	
	return Serializable;
}

void UManifestDiffSummaryLibrary::Break(const UManifestDiffSummary* Serializable, FString& ManifestUid, FString& DiffUrl, int64& CreatedDate)
{
	ManifestUid = Serializable->ManifestUid;
	DiffUrl = Serializable->DiffUrl;
	CreatedDate = Serializable->CreatedDate;
		
}

