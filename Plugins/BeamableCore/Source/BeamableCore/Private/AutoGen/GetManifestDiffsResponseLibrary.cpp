
#include "BeamableCore/Public/AutoGen/GetManifestDiffsResponseLibrary.h"

#include "CoreMinimal.h"


FString UGetManifestDiffsResponseLibrary::GetManifestDiffsResponseToJsonString(const UGetManifestDiffsResponse* Serializable, const bool Pretty)
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

UGetManifestDiffsResponse* UGetManifestDiffsResponseLibrary::Make(bool bHasMore, FString ManifestId, int32 TotalCount, TArray<UManifestDiffSummary*> Diffs, UObject* Outer)
{
	auto Serializable = NewObject<UGetManifestDiffsResponse>(Outer);
	Serializable->bHasMore = bHasMore;
	Serializable->ManifestId = ManifestId;
	Serializable->TotalCount = TotalCount;
	Serializable->Diffs = Diffs;
	
	return Serializable;
}

void UGetManifestDiffsResponseLibrary::Break(const UGetManifestDiffsResponse* Serializable, bool& bHasMore, FString& ManifestId, int32& TotalCount, TArray<UManifestDiffSummary*>& Diffs)
{
	bHasMore = Serializable->bHasMore;
	ManifestId = Serializable->ManifestId;
	TotalCount = Serializable->TotalCount;
	Diffs = Serializable->Diffs;
		
}

