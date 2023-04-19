
#include "BeamableCore/Public/AutoGen/InviteLibrary.h"

#include "CoreMinimal.h"


FString UInviteLibrary::InviteToJsonString(const UInvite* Serializable, const bool Pretty)
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

UInvite* UInviteLibrary::Make(FBeamGamerTag PlayerId, EInvitationDirection Direction, UObject* Outer)
{
	auto Serializable = NewObject<UInvite>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Direction = Direction;
	
	return Serializable;
}

void UInviteLibrary::Break(const UInvite* Serializable, FBeamGamerTag& PlayerId, EInvitationDirection& Direction)
{
	PlayerId = Serializable->PlayerId;
	Direction = Serializable->Direction;
		
}

