
#include "BeamableCore/Public/AutoGen/PullBeamoManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPullBeamoManifestRequestBodyLibrary::PullBeamoManifestRequestBodyToJsonString(const UPullBeamoManifestRequestBody* Serializable, const bool Pretty)
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

UPullBeamoManifestRequestBody* UPullBeamoManifestRequestBodyLibrary::Make(FString SourceRealmPid, UObject* Outer)
{
	auto Serializable = NewObject<UPullBeamoManifestRequestBody>(Outer);
	Serializable->SourceRealmPid = SourceRealmPid;
	
	return Serializable;
}

void UPullBeamoManifestRequestBodyLibrary::Break(const UPullBeamoManifestRequestBody* Serializable, FString& SourceRealmPid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourceRealmPid = Serializable->SourceRealmPid;
	}
		
}

