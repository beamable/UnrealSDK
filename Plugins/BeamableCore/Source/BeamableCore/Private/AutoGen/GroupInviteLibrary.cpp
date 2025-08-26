
#include "BeamableCore/Public/AutoGen/GroupInviteLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupInviteLibrary::GroupInviteToJsonString(const UGroupInvite* Serializable, const bool Pretty)
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

UGroupInvite* UGroupInviteLibrary::Make(int64 GamerTag, FOptionalInt64 SubGroup, FOptionalBool bUseNewRewardsSystem, UObject* Outer)
{
	auto Serializable = NewObject<UGroupInvite>(Outer);
	Serializable->GamerTag = GamerTag;
	Serializable->SubGroup = SubGroup;
	Serializable->bUseNewRewardsSystem = bUseNewRewardsSystem;
	
	return Serializable;
}

void UGroupInviteLibrary::Break(const UGroupInvite* Serializable, int64& GamerTag, FOptionalInt64& SubGroup, FOptionalBool& bUseNewRewardsSystem)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GamerTag = Serializable->GamerTag;
		SubGroup = Serializable->SubGroup;
		bUseNewRewardsSystem = Serializable->bUseNewRewardsSystem;
	}
		
}

