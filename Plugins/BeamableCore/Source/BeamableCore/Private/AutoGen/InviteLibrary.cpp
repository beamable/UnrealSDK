
#include "BeamableCore/Public/AutoGen/InviteLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInviteLibrary::InviteToJsonString(const UInvite* Serializable, const bool Pretty)
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

UInvite* UInviteLibrary::Make(FBeamGamerTag PlayerId, EBeamInvitationDirection Direction, UObject* Outer)
{
	auto Serializable = NewObject<UInvite>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Direction = Direction;
	
	return Serializable;
}

void UInviteLibrary::Break(const UInvite* Serializable, FBeamGamerTag& PlayerId, EBeamInvitationDirection& Direction)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Direction = Serializable->Direction;
	}
		
}

