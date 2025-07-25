
#include "BeamableCore/Public/AutoGen/FriendshipStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UFriendshipStatusLibrary::FriendshipStatusToJsonString(const UFriendshipStatus* Serializable, const bool Pretty)
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

UFriendshipStatus* UFriendshipStatusLibrary::Make(bool bIsBlocked, FBeamGamerTag FriendId, FBeamGamerTag PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UFriendshipStatus>(Outer);
	Serializable->bIsBlocked = bIsBlocked;
	Serializable->FriendId = FriendId;
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UFriendshipStatusLibrary::Break(const UFriendshipStatus* Serializable, bool& bIsBlocked, FBeamGamerTag& FriendId, FBeamGamerTag& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsBlocked = Serializable->bIsBlocked;
		FriendId = Serializable->FriendId;
		PlayerId = Serializable->PlayerId;
	}
		
}

