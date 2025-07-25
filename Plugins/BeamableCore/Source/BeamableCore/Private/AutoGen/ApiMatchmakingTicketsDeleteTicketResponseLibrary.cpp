
#include "BeamableCore/Public/AutoGen/ApiMatchmakingTicketsDeleteTicketResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiMatchmakingTicketsDeleteTicketResponseLibrary::ApiMatchmakingTicketsDeleteTicketResponseToJsonString(const UApiMatchmakingTicketsDeleteTicketResponse* Serializable, const bool Pretty)
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

UApiMatchmakingTicketsDeleteTicketResponse* UApiMatchmakingTicketsDeleteTicketResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiMatchmakingTicketsDeleteTicketResponse>(Outer);
	
	return Serializable;
}



