
#include "BeamableCore/Public/AutoGen/GroupMembershipResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupMembershipResponseLibrary::GroupMembershipResponseToJsonString(const UGroupMembershipResponse* Serializable, const bool Pretty)
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

UGroupMembershipResponse* UGroupMembershipResponseLibrary::Make(bool bMember, EBeamGroupType Type, UGroupMetaData* Group, TArray<int64> SubGroups, FOptionalInt64 GamerTag, UObject* Outer)
{
	auto Serializable = NewObject<UGroupMembershipResponse>(Outer);
	Serializable->bMember = bMember;
	Serializable->Type = Type;
	Serializable->Group = Group;
	Serializable->SubGroups = SubGroups;
	Serializable->GamerTag = GamerTag;
	
	return Serializable;
}

void UGroupMembershipResponseLibrary::Break(const UGroupMembershipResponse* Serializable, bool& bMember, EBeamGroupType& Type, UGroupMetaData*& Group, TArray<int64>& SubGroups, FOptionalInt64& GamerTag)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bMember = Serializable->bMember;
		Type = Serializable->Type;
		Group = Serializable->Group;
		SubGroups = Serializable->SubGroups;
		GamerTag = Serializable->GamerTag;
	}
		
}

