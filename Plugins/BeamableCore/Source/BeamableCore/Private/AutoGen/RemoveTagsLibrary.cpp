
#include "BeamableCore/Public/AutoGen/RemoveTagsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URemoveTagsLibrary::RemoveTagsToJsonString(const URemoveTags* Serializable, const bool Pretty)
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

URemoveTags* URemoveTagsLibrary::Make(FOptionalBeamGamerTag PlayerId, FOptionalArrayOfString Tags, UObject* Outer)
{
	auto Serializable = NewObject<URemoveTags>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void URemoveTagsLibrary::Break(const URemoveTags* Serializable, FOptionalBeamGamerTag& PlayerId, FOptionalArrayOfString& Tags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Tags = Serializable->Tags;
	}
		
}

