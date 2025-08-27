
#include "BeamableCore/Public/AutoGen/PromoteRealmRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPromoteRealmRequestBodyLibrary::PromoteRealmRequestBodyToJsonString(const UPromoteRealmRequestBody* Serializable, const bool Pretty)
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

UPromoteRealmRequestBody* UPromoteRealmRequestBodyLibrary::Make(FBeamPid SourcePid, FOptionalArrayOfString Promotions, FOptionalArrayOfString ContentManifestIds, UObject* Outer)
{
	auto Serializable = NewObject<UPromoteRealmRequestBody>(Outer);
	Serializable->SourcePid = SourcePid;
	Serializable->Promotions = Promotions;
	Serializable->ContentManifestIds = ContentManifestIds;
	
	return Serializable;
}

void UPromoteRealmRequestBodyLibrary::Break(const UPromoteRealmRequestBody* Serializable, FBeamPid& SourcePid, FOptionalArrayOfString& Promotions, FOptionalArrayOfString& ContentManifestIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourcePid = Serializable->SourcePid;
		Promotions = Serializable->Promotions;
		ContentManifestIds = Serializable->ContentManifestIds;
	}
		
}

