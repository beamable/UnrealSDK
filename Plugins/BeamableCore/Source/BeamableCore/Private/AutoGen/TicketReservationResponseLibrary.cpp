
#include "BeamableCore/Public/AutoGen/TicketReservationResponseLibrary.h"

#include "CoreMinimal.h"


FString UTicketReservationResponseLibrary::TicketReservationResponseToJsonString(const UTicketReservationResponse* Serializable, const bool Pretty)
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

UTicketReservationResponse* UTicketReservationResponseLibrary::Make(FOptionalArrayOfTicket Tickets, UObject* Outer)
{
	auto Serializable = NewObject<UTicketReservationResponse>(Outer);
	Serializable->Tickets = Tickets;
	
	return Serializable;
}

void UTicketReservationResponseLibrary::Break(const UTicketReservationResponse* Serializable, FOptionalArrayOfTicket& Tickets)
{
	Tickets = Serializable->Tickets;
		
}

