
#include "BeamableCore/Public/AutoGen/RealmsBasicPromoteRealmRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicPromoteRealmRequestBodyLibrary::RealmsBasicPromoteRealmRequestBodyToJsonString(const URealmsBasicPromoteRealmRequestBody* Serializable, const bool Pretty)
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

URealmsBasicPromoteRealmRequestBody* URealmsBasicPromoteRealmRequestBodyLibrary::Make(FBeamPid SourcePid, FOptionalArrayOfString Promotions, FOptionalArrayOfString ContentManifestIds, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicPromoteRealmRequestBody>(Outer);
	Serializable->SourcePid = SourcePid;
	Serializable->Promotions = Promotions;
	Serializable->ContentManifestIds = ContentManifestIds;
	
	return Serializable;
}

void URealmsBasicPromoteRealmRequestBodyLibrary::Break(const URealmsBasicPromoteRealmRequestBody* Serializable, FBeamPid& SourcePid, FOptionalArrayOfString& Promotions, FOptionalArrayOfString& ContentManifestIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourcePid = Serializable->SourcePid;
		Promotions = Serializable->Promotions;
		ContentManifestIds = Serializable->ContentManifestIds;
	}
		
}

