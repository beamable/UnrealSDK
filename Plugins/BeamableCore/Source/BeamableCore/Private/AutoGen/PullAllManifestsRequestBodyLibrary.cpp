
#include "BeamableCore/Public/AutoGen/PullAllManifestsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPullAllManifestsRequestBodyLibrary::PullAllManifestsRequestBodyToJsonString(const UPullAllManifestsRequestBody* Serializable, const bool Pretty)
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

UPullAllManifestsRequestBody* UPullAllManifestsRequestBodyLibrary::Make(FBeamPid SourceRealmPid, UObject* Outer)
{
	auto Serializable = NewObject<UPullAllManifestsRequestBody>(Outer);
	Serializable->SourceRealmPid = SourceRealmPid;
	
	return Serializable;
}

void UPullAllManifestsRequestBodyLibrary::Break(const UPullAllManifestsRequestBody* Serializable, FBeamPid& SourceRealmPid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourceRealmPid = Serializable->SourceRealmPid;
	}
		
}

