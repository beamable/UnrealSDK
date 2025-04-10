#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Match.h"

#include "MatchLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMatchLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Matchmaking|4 - Json", DisplayName="Match To JSON String")
	static FString MatchToJsonString(const UMatch* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Matchmaking|3 - Backend", DisplayName="Make Match", meta=(DefaultToSelf="Outer", AdvancedDisplay="MatchId, Status, Created, MatchType, Teams, Tickets, Outer", NativeMakeFunc))
	static UMatch* Make(FOptionalString MatchId, FOptionalString Status, FOptionalDateTime Created, FOptionalMatchType MatchType, FOptionalArrayOfTeam Teams, FOptionalArrayOfTicket Tickets, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Matchmaking|3 - Backend", DisplayName="Break Match", meta=(NativeBreakFunc))
	static void Break(const UMatch* Serializable, FOptionalString& MatchId, FOptionalString& Status, FOptionalDateTime& Created, FOptionalMatchType& MatchType, FOptionalArrayOfTeam& Teams, FOptionalArrayOfTicket& Tickets);
};