#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ChallengeSolution.h"

#include "ChallengeSolutionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UChallengeSolutionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="ChallengeSolution To JSON String")
	static FString ChallengeSolutionToJsonString(const UChallengeSolution* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make ChallengeSolution", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UChallengeSolution* Make(FString ChallengeToken, FString Solution, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break ChallengeSolution", meta=(NativeBreakFunc))
	static void Break(const UChallengeSolution* Serializable, FString& ChallengeToken, FString& Solution);
};