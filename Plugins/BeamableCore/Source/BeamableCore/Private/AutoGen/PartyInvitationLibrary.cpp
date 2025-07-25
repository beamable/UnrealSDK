
#include "BeamableCore/Public/AutoGen/PartyInvitationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPartyInvitationLibrary::PartyInvitationToJsonString(const UPartyInvitation* Serializable, const bool Pretty)
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

UPartyInvitation* UPartyInvitationLibrary::Make(FOptionalString PartyId, FOptionalString InvitedBy, UObject* Outer)
{
	auto Serializable = NewObject<UPartyInvitation>(Outer);
	Serializable->PartyId = PartyId;
	Serializable->InvitedBy = InvitedBy;
	
	return Serializable;
}

void UPartyInvitationLibrary::Break(const UPartyInvitation* Serializable, FOptionalString& PartyId, FOptionalString& InvitedBy)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PartyId = Serializable->PartyId;
		InvitedBy = Serializable->InvitedBy;
	}
		
}

