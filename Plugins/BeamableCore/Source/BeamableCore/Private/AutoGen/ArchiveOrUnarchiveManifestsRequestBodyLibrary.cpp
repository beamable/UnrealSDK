
#include "BeamableCore/Public/AutoGen/ArchiveOrUnarchiveManifestsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UArchiveOrUnarchiveManifestsRequestBodyLibrary::ArchiveOrUnarchiveManifestsRequestBodyToJsonString(const UArchiveOrUnarchiveManifestsRequestBody* Serializable, const bool Pretty)
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

UArchiveOrUnarchiveManifestsRequestBody* UArchiveOrUnarchiveManifestsRequestBodyLibrary::Make(TArray<FBeamContentManifestId> ManifestIds, UObject* Outer)
{
	auto Serializable = NewObject<UArchiveOrUnarchiveManifestsRequestBody>(Outer);
	Serializable->ManifestIds = ManifestIds;
	
	return Serializable;
}

void UArchiveOrUnarchiveManifestsRequestBodyLibrary::Break(const UArchiveOrUnarchiveManifestsRequestBody* Serializable, TArray<FBeamContentManifestId>& ManifestIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ManifestIds = Serializable->ManifestIds;
	}
		
}

