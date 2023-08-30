#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Ticket.h"

#include "TicketLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTicketLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Ticket To JSON String")
	static FString TicketToJsonString(const UTicket* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Ticket", meta=(DefaultToSelf="Outer", AdvancedDisplay="bWatchOnlineStatus, TicketId, Status, Created, Expires, MatchType, MatchId, Team, Priority, PartyId, Players, StringProperties, NumberProperties, Outer", NativeMakeFunc))
	static UTicket* Make(FOptionalBool bWatchOnlineStatus, FOptionalString TicketId, FOptionalString Status, FOptionalString Created, FOptionalString Expires, FOptionalBeamContentId MatchType, FOptionalString MatchId, FOptionalString Team, FOptionalInt32 Priority, FOptionalString PartyId, FOptionalArrayOfString Players, FOptionalMapOfString StringProperties, FOptionalMapOfDouble NumberProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Ticket", meta=(NativeBreakFunc))
	static void Break(const UTicket* Serializable, FOptionalBool& bWatchOnlineStatus, FOptionalString& TicketId, FOptionalString& Status, FOptionalString& Created, FOptionalString& Expires, FOptionalBeamContentId& MatchType, FOptionalString& MatchId, FOptionalString& Team, FOptionalInt32& Priority, FOptionalString& PartyId, FOptionalArrayOfString& Players, FOptionalMapOfString& StringProperties, FOptionalMapOfDouble& NumberProperties);
};