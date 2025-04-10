#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Event.h"

#include "EventLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="Event To JSON String")
	static FString EventToJsonString(const UEvent* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make Event", meta=(DefaultToSelf="Outer", AdvancedDisplay="PartitionSize, GroupRewards, CohortSettings, Permissions, Schedule, Stores, ScoreRewards, RankRewards, Outer", NativeMakeFunc))
	static UEvent* Make(FString Name, FString StartDate, FString Symbol, TArray<UEventPhase*> Phases, FOptionalInt32 PartitionSize, FOptionalEventGroupRewards GroupRewards, FOptionalLeaderboardCohortSettings CohortSettings, FOptionalBeamClientPermission Permissions, FOptionalSchedule Schedule, FOptionalArrayOfString Stores, FOptionalArrayOfEventRewardContent ScoreRewards, FOptionalArrayOfEventRewardContent RankRewards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break Event", meta=(NativeBreakFunc))
	static void Break(const UEvent* Serializable, FString& Name, FString& StartDate, FString& Symbol, TArray<UEventPhase*>& Phases, FOptionalInt32& PartitionSize, FOptionalEventGroupRewards& GroupRewards, FOptionalLeaderboardCohortSettings& CohortSettings, FOptionalBeamClientPermission& Permissions, FOptionalSchedule& Schedule, FOptionalArrayOfString& Stores, FOptionalArrayOfEventRewardContent& ScoreRewards, FOptionalArrayOfEventRewardContent& RankRewards);
};