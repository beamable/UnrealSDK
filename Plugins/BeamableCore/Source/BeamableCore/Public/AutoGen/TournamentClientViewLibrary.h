#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TournamentClientView.h"

#include "TournamentClientViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTournamentClientViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="TournamentClientView To JSON String")
	static FString TournamentClientViewToJsonString(const UTournamentClientView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make TournamentClientView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UTournamentClientView* Make(FString TournamentId, FString StartTimeUtc, int64 SecondsRemaining, int32 Cycle, FString EndTimeUtc, FString ContentId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break TournamentClientView", meta=(NativeBreakFunc))
	static void Break(const UTournamentClientView* Serializable, FString& TournamentId, FString& StartTimeUtc, int64& SecondsRemaining, int32& Cycle, FString& EndTimeUtc, FString& ContentId);
};