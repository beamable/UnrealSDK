
#include "BeamableCore/Public/AutoGen/TicketQueryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTicketQueryResponseLibrary::TicketQueryResponseToJsonString(const UTicketQueryResponse* Serializable, const bool Pretty)
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

UTicketQueryResponse* UTicketQueryResponseLibrary::Make(FOptionalArrayOfTicket Results, UObject* Outer)
{
	auto Serializable = NewObject<UTicketQueryResponse>(Outer);
	Serializable->Results = Results;
	
	return Serializable;
}

void UTicketQueryResponseLibrary::Break(const UTicketQueryResponse* Serializable, FOptionalArrayOfTicket& Results)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Results = Serializable->Results;
	}
		
}

