
#include "BeamableCore/Public/AutoGen/RemoveTagsLibrary.h"

#include "CoreMinimal.h"


FString URemoveTagsLibrary::RemoveTagsToJsonString(const URemoveTags* Serializable, const bool Pretty)
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

URemoveTags* URemoveTagsLibrary::Make(FOptionalString PlayerId, FOptionalArrayOfString Tags, UObject* Outer)
{
	auto Serializable = NewObject<URemoveTags>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void URemoveTagsLibrary::Break(const URemoveTags* Serializable, FOptionalString& PlayerId, FOptionalArrayOfString& Tags)
{
	PlayerId = Serializable->PlayerId;
	Tags = Serializable->Tags;
		
}

