
#include "BeamableCore/Public/AutoGen/CancelInviteToPartyLibrary.h"

#include "CoreMinimal.h"


FString UCancelInviteToPartyLibrary::CancelInviteToPartyToJsonString(const UCancelInviteToParty* Serializable, const bool Pretty)
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

UCancelInviteToParty* UCancelInviteToPartyLibrary::Make(FOptionalBeamGamerTag PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UCancelInviteToParty>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UCancelInviteToPartyLibrary::Break(const UCancelInviteToParty* Serializable, FOptionalBeamGamerTag& PlayerId)
{
	PlayerId = Serializable->PlayerId;
		
}

