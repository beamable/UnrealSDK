
#include "BeamableCore/Public/AutoGen/GroupUserLibrary.h"

#include "CoreMinimal.h"


FString UGroupUserLibrary::GroupUserToJsonString(const UGroupUser* Serializable, const bool Pretty)
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

UGroupUser* UGroupUserLibrary::Make(int64 GamerTag, int64 Updated, TArray<UGroupUserMember*> AllGroups, TMap<FString, FArrayOfString> Member, FOptionalArrayOfInFlightMessage InFlight, FOptionalArrayOfGroupScoreBinding Scores, UObject* Outer)
{
	auto Serializable = NewObject<UGroupUser>(Outer);
	Serializable->GamerTag = GamerTag;
	Serializable->Updated = Updated;
	Serializable->AllGroups = AllGroups;
	Serializable->Member = Member;
	Serializable->InFlight = InFlight;
	Serializable->Scores = Scores;
	
	return Serializable;
}

void UGroupUserLibrary::Break(const UGroupUser* Serializable, int64& GamerTag, int64& Updated, TArray<UGroupUserMember*>& AllGroups, TMap<FString, FArrayOfString>& Member, FOptionalArrayOfInFlightMessage& InFlight, FOptionalArrayOfGroupScoreBinding& Scores)
{
	GamerTag = Serializable->GamerTag;
	Updated = Serializable->Updated;
	AllGroups = Serializable->AllGroups;
	Member = Serializable->Member;
	InFlight = Serializable->InFlight;
	Scores = Serializable->Scores;
		
}

