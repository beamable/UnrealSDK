
#include "BeamableCore/Public/AutoGen/AddTagsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAddTagsLibrary::AddTagsToJsonString(const UAddTags* Serializable, const bool Pretty)
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

UAddTags* UAddTagsLibrary::Make(FOptionalBeamGamerTag PlayerId, FOptionalBool bReplace, FOptionalArrayOfBeamTag Tags, UObject* Outer)
{
	auto Serializable = NewObject<UAddTags>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->bReplace = bReplace;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UAddTagsLibrary::Break(const UAddTags* Serializable, FOptionalBeamGamerTag& PlayerId, FOptionalBool& bReplace, FOptionalArrayOfBeamTag& Tags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		bReplace = Serializable->bReplace;
		Tags = Serializable->Tags;
	}
		
}

