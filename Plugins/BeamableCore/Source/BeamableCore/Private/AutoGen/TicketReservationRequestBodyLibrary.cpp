
#include "BeamableCore/Public/AutoGen/TicketReservationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTicketReservationRequestBodyLibrary::TicketReservationRequestBodyToJsonString(const UTicketReservationRequestBody* Serializable, const bool Pretty)
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

UTicketReservationRequestBody* UTicketReservationRequestBodyLibrary::Make(FOptionalBool bWatchOnlineStatus, FOptionalInt32 MaxWaitDurationSecs, FOptionalString Team, FOptionalArrayOfBeamGamerTag Players, FOptionalArrayOfBeamContentId MatchTypes, FOptionalArrayOfBeamTag Tags, UObject* Outer)
{
	auto Serializable = NewObject<UTicketReservationRequestBody>(Outer);
	Serializable->bWatchOnlineStatus = bWatchOnlineStatus;
	Serializable->MaxWaitDurationSecs = MaxWaitDurationSecs;
	Serializable->Team = Team;
	Serializable->Players = Players;
	Serializable->MatchTypes = MatchTypes;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UTicketReservationRequestBodyLibrary::Break(const UTicketReservationRequestBody* Serializable, FOptionalBool& bWatchOnlineStatus, FOptionalInt32& MaxWaitDurationSecs, FOptionalString& Team, FOptionalArrayOfBeamGamerTag& Players, FOptionalArrayOfBeamContentId& MatchTypes, FOptionalArrayOfBeamTag& Tags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bWatchOnlineStatus = Serializable->bWatchOnlineStatus;
		MaxWaitDurationSecs = Serializable->MaxWaitDurationSecs;
		Team = Serializable->Team;
		Players = Serializable->Players;
		MatchTypes = Serializable->MatchTypes;
		Tags = Serializable->Tags;
	}
		
}

