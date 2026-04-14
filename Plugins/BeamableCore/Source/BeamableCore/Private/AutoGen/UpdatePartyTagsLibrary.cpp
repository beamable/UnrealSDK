
#include "BeamableCore/Public/AutoGen/UpdatePartyTagsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdatePartyTagsLibrary::UpdatePartyTagsToJsonString(const UUpdatePartyTags* Serializable, const bool Pretty)
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

UUpdatePartyTags* UUpdatePartyTagsLibrary::Make(FOptionalString PlayerId, FOptionalArrayOfBeamTag MemberTags, UObject* Outer)
{
	auto Serializable = NewObject<UUpdatePartyTags>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->MemberTags = MemberTags;
	
	return Serializable;
}

void UUpdatePartyTagsLibrary::Break(const UUpdatePartyTags* Serializable, FOptionalString& PlayerId, FOptionalArrayOfBeamTag& MemberTags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		MemberTags = Serializable->MemberTags;
	}
		
}

