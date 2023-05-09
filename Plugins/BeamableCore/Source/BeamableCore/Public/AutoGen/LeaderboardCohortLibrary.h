#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardCohort.h"

#include "LeaderboardCohortLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardCohortLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardCohort To JSON String")
	static FString LeaderboardCohortToJsonString(const ULeaderboardCohort* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardCohort", meta=(DefaultToSelf="Outer", AdvancedDisplay="Description, Outer", NativeMakeFunc))
	static ULeaderboardCohort* Make(FString Id, TArray<UPlayerStatRequirement*> StatRequirements, FOptionalString Description, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardCohort", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardCohort* Serializable, FString& Id, TArray<UPlayerStatRequirement*>& StatRequirements, FOptionalString& Description);
};