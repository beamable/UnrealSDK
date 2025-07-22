
#include "BeamableCore/Public/AutoGen/ContentBasicGetManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UContentBasicGetManifestRequestBodyLibrary::ContentBasicGetManifestRequestBodyToJsonString(const UContentBasicGetManifestRequestBody* Serializable, const bool Pretty)
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

UContentBasicGetManifestRequestBody* UContentBasicGetManifestRequestBodyLibrary::Make(FOptionalBeamContentManifestId Id, FOptionalString Uid, UObject* Outer)
{
	auto Serializable = NewObject<UContentBasicGetManifestRequestBody>(Outer);
	Serializable->Id = Id;
	Serializable->Uid = Uid;
	
	return Serializable;
}

void UContentBasicGetManifestRequestBodyLibrary::Break(const UContentBasicGetManifestRequestBody* Serializable, FOptionalBeamContentManifestId& Id, FOptionalString& Uid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Uid = Serializable->Uid;
	}
		
}

