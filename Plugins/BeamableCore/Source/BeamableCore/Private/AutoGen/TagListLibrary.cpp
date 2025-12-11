
#include "BeamableCore/Public/AutoGen/TagListLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTagListLibrary::TagListToJsonString(const UTagList* Serializable, const bool Pretty)
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

UTagList* UTagListLibrary::Make(FOptionalArrayOfBeamTag Tags, UObject* Outer)
{
	auto Serializable = NewObject<UTagList>(Outer);
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UTagListLibrary::Break(const UTagList* Serializable, FOptionalArrayOfBeamTag& Tags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Tags = Serializable->Tags;
	}
		
}

