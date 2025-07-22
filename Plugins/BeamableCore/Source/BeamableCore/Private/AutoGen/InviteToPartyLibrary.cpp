
#include "BeamableCore/Public/AutoGen/InviteToPartyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInviteToPartyLibrary::InviteToPartyToJsonString(const UInviteToParty* Serializable, const bool Pretty)
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

UInviteToParty* UInviteToPartyLibrary::Make(FOptionalBeamGamerTag PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UInviteToParty>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UInviteToPartyLibrary::Break(const UInviteToParty* Serializable, FOptionalBeamGamerTag& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
	}
		
}

