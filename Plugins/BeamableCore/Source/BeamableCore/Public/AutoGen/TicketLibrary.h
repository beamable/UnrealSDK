#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Ticket.h"

#include "TicketLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTicketLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|PlayerTicket|Utils|Json", DisplayName="Ticket To JSON String")
	static FString TicketToJsonString(const UTicket* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|PlayerTicket|Utils|Make/Break", DisplayName="Make Ticket", meta=(DefaultToSelf="Outer", AdvancedDisplay="bWatchOnlineStatus, TicketId, Status, Created, Expires, MatchType, MatchId, Team, Priority, PartyId, LobbyId, Players, Tags, StringProperties, NumberProperties, Outer", NativeMakeFunc))
	static UTicket* Make(FOptionalBool bWatchOnlineStatus, FOptionalString TicketId, FOptionalString Status, FOptionalDateTime Created, FOptionalDateTime Expires, FOptionalBeamContentId MatchType, FOptionalString MatchId, FOptionalString Team, FOptionalInt32 Priority, FOptionalString PartyId, FOptionalString LobbyId, FOptionalArrayOfBeamGamerTag Players, FOptionalArrayOfBeamTag Tags, FOptionalMapOfString StringProperties, FOptionalMapOfDouble NumberProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|PlayerTicket|Utils|Make/Break", DisplayName="Break Ticket", meta=(NativeBreakFunc))
	static void Break(const UTicket* Serializable, FOptionalBool& bWatchOnlineStatus, FOptionalString& TicketId, FOptionalString& Status, FOptionalDateTime& Created, FOptionalDateTime& Expires, FOptionalBeamContentId& MatchType, FOptionalString& MatchId, FOptionalString& Team, FOptionalInt32& Priority, FOptionalString& PartyId, FOptionalString& LobbyId, FOptionalArrayOfBeamGamerTag& Players, FOptionalArrayOfBeamTag& Tags, FOptionalMapOfString& StringProperties, FOptionalMapOfDouble& NumberProperties);
};