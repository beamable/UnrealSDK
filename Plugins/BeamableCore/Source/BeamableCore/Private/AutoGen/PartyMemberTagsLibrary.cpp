
#include "BeamableCore/Public/AutoGen/PartyMemberTagsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPartyMemberTagsLibrary::PartyMemberTagsToJsonString(const UPartyMemberTags* Serializable, const bool Pretty)
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

UPartyMemberTags* UPartyMemberTagsLibrary::Make(FOptionalArrayOfBeamTag MemberTags, UObject* Outer)
{
	auto Serializable = NewObject<UPartyMemberTags>(Outer);
	Serializable->MemberTags = MemberTags;
	
	return Serializable;
}

void UPartyMemberTagsLibrary::Break(const UPartyMemberTags* Serializable, FOptionalArrayOfBeamTag& MemberTags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MemberTags = Serializable->MemberTags;
	}
		
}

