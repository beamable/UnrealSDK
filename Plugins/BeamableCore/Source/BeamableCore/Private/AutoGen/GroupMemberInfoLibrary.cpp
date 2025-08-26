
#include "BeamableCore/Public/AutoGen/GroupMemberInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupMemberInfoLibrary::GroupMemberInfoToJsonString(const UGroupMemberInfo* Serializable, const bool Pretty)
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

UGroupMemberInfo* UGroupMemberInfoLibrary::Make(FOptionalArrayOfGroupUserMember Guild, FOptionalArrayOfGroupUserMember Subgroup, UObject* Outer)
{
	auto Serializable = NewObject<UGroupMemberInfo>(Outer);
	Serializable->Guild = Guild;
	Serializable->Subgroup = Subgroup;
	
	return Serializable;
}

void UGroupMemberInfoLibrary::Break(const UGroupMemberInfo* Serializable, FOptionalArrayOfGroupUserMember& Guild, FOptionalArrayOfGroupUserMember& Subgroup)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Guild = Serializable->Guild;
		Subgroup = Serializable->Subgroup;
	}
		
}

