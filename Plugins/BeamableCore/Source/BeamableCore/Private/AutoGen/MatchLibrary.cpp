
#include "BeamableCore/Public/AutoGen/MatchLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMatchLibrary::MatchToJsonString(const UMatch* Serializable, const bool Pretty)
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

UMatch* UMatchLibrary::Make(FOptionalString MatchId, FOptionalString Status, FOptionalDateTime Created, FOptionalMatchType MatchType, FOptionalArrayOfTeam Teams, FOptionalArrayOfTicket Tickets, UObject* Outer)
{
	auto Serializable = NewObject<UMatch>(Outer);
	Serializable->MatchId = MatchId;
	Serializable->Status = Status;
	Serializable->Created = Created;
	Serializable->MatchType = MatchType;
	Serializable->Teams = Teams;
	Serializable->Tickets = Tickets;
	
	return Serializable;
}

void UMatchLibrary::Break(const UMatch* Serializable, FOptionalString& MatchId, FOptionalString& Status, FOptionalDateTime& Created, FOptionalMatchType& MatchType, FOptionalArrayOfTeam& Teams, FOptionalArrayOfTicket& Tickets)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MatchId = Serializable->MatchId;
		Status = Serializable->Status;
		Created = Serializable->Created;
		MatchType = Serializable->MatchType;
		Teams = Serializable->Teams;
		Tickets = Serializable->Tickets;
	}
		
}

