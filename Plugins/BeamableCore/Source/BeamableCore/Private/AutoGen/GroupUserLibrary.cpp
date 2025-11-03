
#include "BeamableCore/Public/AutoGen/GroupUserLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupUserLibrary::GroupUserToJsonString(const UGroupUser* Serializable, const bool Pretty)
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

UGroupUser* UGroupUserLibrary::Make(int64 GamerTag, int64 Updated, UGroupMemberInfo* Member, TArray<UGroupUserMember*> AllGroups, FOptionalArrayOfInFlightMessage InFlight, FOptionalArrayOfGroupScoreBinding Scores, UObject* Outer)
{
	auto Serializable = NewObject<UGroupUser>(Outer);
	Serializable->GamerTag = GamerTag;
	Serializable->Updated = Updated;
	Serializable->Member = Member;
	Serializable->AllGroups = AllGroups;
	Serializable->InFlight = InFlight;
	Serializable->Scores = Scores;
	
	return Serializable;
}

void UGroupUserLibrary::Break(const UGroupUser* Serializable, int64& GamerTag, int64& Updated, UGroupMemberInfo*& Member, TArray<UGroupUserMember*>& AllGroups, FOptionalArrayOfInFlightMessage& InFlight, FOptionalArrayOfGroupScoreBinding& Scores)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GamerTag = Serializable->GamerTag;
		Updated = Serializable->Updated;
		Member = Serializable->Member;
		AllGroups = Serializable->AllGroups;
		InFlight = Serializable->InFlight;
		Scores = Serializable->Scores;
	}
		
}

