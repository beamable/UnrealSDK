
#include "BeamableCore/Public/AutoGen/PullManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPullManifestRequestBodyLibrary::PullManifestRequestBodyToJsonString(const UPullManifestRequestBody* Serializable, const bool Pretty)
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

UPullManifestRequestBody* UPullManifestRequestBodyLibrary::Make(FBeamPid SourceRealmPid, FOptionalBeamContentManifestId Id, UObject* Outer)
{
	auto Serializable = NewObject<UPullManifestRequestBody>(Outer);
	Serializable->SourceRealmPid = SourceRealmPid;
	Serializable->Id = Id;
	
	return Serializable;
}

void UPullManifestRequestBodyLibrary::Break(const UPullManifestRequestBody* Serializable, FBeamPid& SourceRealmPid, FOptionalBeamContentManifestId& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourceRealmPid = Serializable->SourceRealmPid;
		Id = Serializable->Id;
	}
		
}

