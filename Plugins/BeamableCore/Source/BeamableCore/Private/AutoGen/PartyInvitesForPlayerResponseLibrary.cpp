
#include "BeamableCore/Public/AutoGen/PartyInvitesForPlayerResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPartyInvitesForPlayerResponseLibrary::PartyInvitesForPlayerResponseToJsonString(const UPartyInvitesForPlayerResponse* Serializable, const bool Pretty)
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

UPartyInvitesForPlayerResponse* UPartyInvitesForPlayerResponseLibrary::Make(FOptionalArrayOfPartyInvitation Invitations, UObject* Outer)
{
	auto Serializable = NewObject<UPartyInvitesForPlayerResponse>(Outer);
	Serializable->Invitations = Invitations;
	
	return Serializable;
}

void UPartyInvitesForPlayerResponseLibrary::Break(const UPartyInvitesForPlayerResponse* Serializable, FOptionalArrayOfPartyInvitation& Invitations)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Invitations = Serializable->Invitations;
	}
		
}

