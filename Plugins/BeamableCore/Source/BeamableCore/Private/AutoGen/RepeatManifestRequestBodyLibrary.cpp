
#include "BeamableCore/Public/AutoGen/RepeatManifestRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URepeatManifestRequestBodyLibrary::RepeatManifestRequestBodyToJsonString(const URepeatManifestRequestBody* Serializable, const bool Pretty)
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

URepeatManifestRequestBody* URepeatManifestRequestBodyLibrary::Make(FString Uid, UObject* Outer)
{
	auto Serializable = NewObject<URepeatManifestRequestBody>(Outer);
	Serializable->Uid = Uid;
	
	return Serializable;
}

void URepeatManifestRequestBodyLibrary::Break(const URepeatManifestRequestBody* Serializable, FString& Uid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Uid = Serializable->Uid;
	}
		
}

