#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/ChallengeSolution.h"

#include "ChallengeSolutionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UChallengeSolutionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ChallengeSolution To JSON String")
	static FString ChallengeSolutionToJsonString(const UChallengeSolution* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ChallengeSolution", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UChallengeSolution* Make(FString ChallengeToken, FString Solution, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ChallengeSolution", meta=(NativeBreakFunc))
	static void Break(const UChallengeSolution* Serializable, FString& ChallengeToken, FString& Solution);
};