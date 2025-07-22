
#include "BeamableCore/Public/AutoGen/GroupUserMemberLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupUserMemberLibrary::GroupUserMemberToJsonString(const UGroupUserMember* Serializable, const bool Pretty)
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

UGroupUserMember* UGroupUserMemberLibrary::Make(int64 Id, TArray<UGroupUserMember*> SubGroups, FOptionalInt64 Joined, UObject* Outer)
{
	auto Serializable = NewObject<UGroupUserMember>(Outer);
	Serializable->Id = Id;
	Serializable->SubGroups = SubGroups;
	Serializable->Joined = Joined;
	
	return Serializable;
}

void UGroupUserMemberLibrary::Break(const UGroupUserMember* Serializable, int64& Id, TArray<UGroupUserMember*>& SubGroups, FOptionalInt64& Joined)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		SubGroups = Serializable->SubGroups;
		Joined = Serializable->Joined;
	}
		
}

