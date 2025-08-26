
#include "BeamableCore/Public/AutoGen/GetTemplateRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetTemplateRequestBodyLibrary::GetTemplateRequestBodyToJsonString(const UGetTemplateRequestBody* Serializable, const bool Pretty)
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

UGetTemplateRequestBody* UGetTemplateRequestBodyLibrary::Make(FString TemplateName, int64 GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<UGetTemplateRequestBody>(Outer);
	Serializable->TemplateName = TemplateName;
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void UGetTemplateRequestBodyLibrary::Break(const UGetTemplateRequestBody* Serializable, FString& TemplateName, int64& GamerTag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TemplateName = Serializable->TemplateName;
		GamerTag = Serializable->GamerTag;
	}
		
}

