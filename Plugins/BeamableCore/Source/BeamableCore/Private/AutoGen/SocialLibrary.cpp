
#include "BeamableCore/Public/AutoGen/SocialLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USocialLibrary::SocialToJsonString(const USocial* Serializable, const bool Pretty)
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

USocial* USocialLibrary::Make(FBeamGamerTag PlayerId, TArray<UFriend*> Friends, TArray<UPlayerId*> Blocked, TArray<UInvite*> Invites, UObject* Outer)
{
	auto Serializable = NewObject<USocial>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Friends = Friends;
	Serializable->Blocked = Blocked;
	Serializable->Invites = Invites;
	
	return Serializable;
}

void USocialLibrary::Break(const USocial* Serializable, FBeamGamerTag& PlayerId, TArray<UFriend*>& Friends, TArray<UPlayerId*>& Blocked, TArray<UInvite*>& Invites)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Friends = Serializable->Friends;
		Blocked = Serializable->Blocked;
		Invites = Serializable->Invites;
	}
		
}

