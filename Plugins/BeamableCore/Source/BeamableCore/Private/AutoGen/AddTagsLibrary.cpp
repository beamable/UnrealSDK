
#include "BeamableCore/Public/AutoGen/AddTagsLibrary.h"

#include "CoreMinimal.h"


FString UAddTagsLibrary::AddTagsToJsonString(const UAddTags* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UAddTags* UAddTagsLibrary::Make(FOptionalString PlayerId, FOptionalBool bReplace, FOptionalArrayOfTag Tags, UObject* Outer)
{
	auto Serializable = NewObject<UAddTags>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->bReplace = bReplace;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UAddTagsLibrary::Break(const UAddTags* Serializable, FOptionalString& PlayerId, FOptionalBool& bReplace, FOptionalArrayOfTag& Tags)
{
	PlayerId = Serializable->PlayerId;
	bReplace = Serializable->bReplace;
	Tags = Serializable->Tags;
		
}

