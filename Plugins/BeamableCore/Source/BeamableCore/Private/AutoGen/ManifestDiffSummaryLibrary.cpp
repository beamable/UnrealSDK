
#include "BeamableCore/Public/AutoGen/ManifestDiffSummaryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


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

UManifestDiffSummary* UManifestDiffSummaryLibrary::Make(FString ManifestUid, int64 CreatedDate, TArray<FString> AffectedContentIds, FOptionalString PublishedByName, FOptionalString PublishedBy, UObject* Outer)
{
	auto Serializable = NewObject<UManifestDiffSummary>(Outer);
	Serializable->ManifestUid = ManifestUid;
	Serializable->CreatedDate = CreatedDate;
	Serializable->AffectedContentIds = AffectedContentIds;
	Serializable->PublishedByName = PublishedByName;
	Serializable->PublishedBy = PublishedBy;
	
	return Serializable;
}

void UManifestDiffSummaryLibrary::Break(const UManifestDiffSummary* Serializable, FString& ManifestUid, int64& CreatedDate, TArray<FString>& AffectedContentIds, FOptionalString& PublishedByName, FOptionalString& PublishedBy)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ManifestUid = Serializable->ManifestUid;
		CreatedDate = Serializable->CreatedDate;
		AffectedContentIds = Serializable->AffectedContentIds;
		PublishedByName = Serializable->PublishedByName;
		PublishedBy = Serializable->PublishedBy;
	}
		
}

