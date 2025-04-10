#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TicketReservationRequestBody.h"

#include "TicketReservationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTicketReservationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Matchmaking|Utils|Json", DisplayName="TicketReservationRequestBody To JSON String")
	static FString TicketReservationRequestBodyToJsonString(const UTicketReservationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Matchmaking|Utils|Make/Break", DisplayName="Make TicketReservationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bWatchOnlineStatus, MaxWaitDurationSecs, Team, Players, MatchTypes, Tags, Outer", NativeMakeFunc))
	static UTicketReservationRequestBody* Make(FOptionalBool bWatchOnlineStatus, FOptionalInt32 MaxWaitDurationSecs, FOptionalString Team, FOptionalArrayOfBeamGamerTag Players, FOptionalArrayOfBeamContentId MatchTypes, FOptionalArrayOfBeamTag Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Matchmaking|Utils|Make/Break", DisplayName="Break TicketReservationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UTicketReservationRequestBody* Serializable, FOptionalBool& bWatchOnlineStatus, FOptionalInt32& MaxWaitDurationSecs, FOptionalString& Team, FOptionalArrayOfBeamGamerTag& Players, FOptionalArrayOfBeamContentId& MatchTypes, FOptionalArrayOfBeamTag& Tags);
};