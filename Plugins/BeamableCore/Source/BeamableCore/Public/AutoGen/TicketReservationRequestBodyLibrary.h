#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TicketReservationRequestBody.h"

#include "TicketReservationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTicketReservationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TicketReservationRequestBody To JSON String")
	static FString TicketReservationRequestBodyToJsonString(const UTicketReservationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TicketReservationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bWatchOnlineStatus, MaxWaitDurationSecs, Team, Players, MatchTypes, Outer", NativeMakeFunc))
	static UTicketReservationRequestBody* Make(FOptionalBool bWatchOnlineStatus, FOptionalInt32 MaxWaitDurationSecs, FOptionalString Team, FOptionalArrayOfString Players, FOptionalArrayOfBeamContentId MatchTypes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TicketReservationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UTicketReservationRequestBody* Serializable, FOptionalBool& bWatchOnlineStatus, FOptionalInt32& MaxWaitDurationSecs, FOptionalString& Team, FOptionalArrayOfString& Players, FOptionalArrayOfBeamContentId& MatchTypes);
};