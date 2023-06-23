
#include "BeamableCore/Public/AutoGen/InviteToPartyLibrary.h"

#include "CoreMinimal.h"


FString UInviteToPartyLibrary::InviteToPartyToJsonString(const UInviteToParty* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UInviteToParty* UInviteToPartyLibrary::Make(FOptionalString PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UInviteToParty>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UInviteToPartyLibrary::Break(const UInviteToParty* Serializable, FOptionalString& PlayerId)
{
	PlayerId = Serializable->PlayerId;
		
}

