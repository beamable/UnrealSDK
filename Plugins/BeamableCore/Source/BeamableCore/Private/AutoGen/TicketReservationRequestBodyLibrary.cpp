
#include "BeamableCore/Public/AutoGen/TicketReservationRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UTicketReservationRequestBodyLibrary::TicketReservationRequestBodyToJsonString(const UTicketReservationRequestBody* Serializable, const bool Pretty)
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

UTicketReservationRequestBody* UTicketReservationRequestBodyLibrary::Make(FOptionalBool bWatchOnlineStatus, FOptionalBeamContentId MatchTypes, FOptionalInt32 MaxWaitDurationSecs, FOptionalString Team, FOptionalArrayOfString Players, UObject* Outer)
{
	auto Serializable = NewObject<UTicketReservationRequestBody>(Outer);
	Serializable->bWatchOnlineStatus = bWatchOnlineStatus;
	Serializable->MatchTypes = MatchTypes;
	Serializable->MaxWaitDurationSecs = MaxWaitDurationSecs;
	Serializable->Team = Team;
	Serializable->Players = Players;
	
	return Serializable;
}

void UTicketReservationRequestBodyLibrary::Break(const UTicketReservationRequestBody* Serializable, FOptionalBool& bWatchOnlineStatus, FOptionalBeamContentId& MatchTypes, FOptionalInt32& MaxWaitDurationSecs, FOptionalString& Team, FOptionalArrayOfString& Players)
{
	bWatchOnlineStatus = Serializable->bWatchOnlineStatus;
	MatchTypes = Serializable->MatchTypes;
	MaxWaitDurationSecs = Serializable->MaxWaitDurationSecs;
	Team = Serializable->Team;
	Players = Serializable->Players;
		
}

