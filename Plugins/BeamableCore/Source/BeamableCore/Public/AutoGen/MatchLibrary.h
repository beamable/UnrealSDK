#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Match.h"

#include "MatchLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMatchLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Match To JSON String")
	static FString MatchToJsonString(const UMatch* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Match", meta=(DefaultToSelf="Outer", AdvancedDisplay="MatchId, Status, Created, MatchType, Teams, Tickets, Outer", NativeMakeFunc))
	static UMatch* Make(FOptionalString MatchId, FOptionalString Status, FOptionalString Created, FOptionalMatchType MatchType, FOptionalArrayOfTeam Teams, FOptionalArrayOfTicket Tickets, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Match", meta=(NativeBreakFunc))
	static void Break(const UMatch* Serializable, FOptionalString& MatchId, FOptionalString& Status, FOptionalString& Created, FOptionalMatchType& MatchType, FOptionalArrayOfTeam& Teams, FOptionalArrayOfTicket& Tickets);
};