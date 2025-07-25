
#include "BeamableCore/Public/AutoGen/ListTagsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListTagsRequestBodyLibrary::ListTagsRequestBodyToJsonString(const UListTagsRequestBody* Serializable, const bool Pretty)
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

UListTagsRequestBody* UListTagsRequestBodyLibrary::Make(FOptionalString TagNameFilter, UObject* Outer)
{
	auto Serializable = NewObject<UListTagsRequestBody>(Outer);
	Serializable->TagNameFilter = TagNameFilter;
	
	return Serializable;
}

void UListTagsRequestBodyLibrary::Break(const UListTagsRequestBody* Serializable, FOptionalString& TagNameFilter)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TagNameFilter = Serializable->TagNameFilter;
	}
		
}

