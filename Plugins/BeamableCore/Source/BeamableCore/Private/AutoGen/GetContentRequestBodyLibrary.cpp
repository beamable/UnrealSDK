
#include "BeamableCore/Public/AutoGen/GetContentRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetContentRequestBodyLibrary::GetContentRequestBodyToJsonString(const UGetContentRequestBody* Serializable, const bool Pretty)
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

UGetContentRequestBody* UGetContentRequestBodyLibrary::Make(FBeamContentId ContentId, FString Version, UObject* Outer)
{
	auto Serializable = NewObject<UGetContentRequestBody>(Outer);
	Serializable->ContentId = ContentId;
	Serializable->Version = Version;
	
	return Serializable;
}

void UGetContentRequestBodyLibrary::Break(const UGetContentRequestBody* Serializable, FBeamContentId& ContentId, FString& Version)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentId = Serializable->ContentId;
		Version = Serializable->Version;
	}
		
}

