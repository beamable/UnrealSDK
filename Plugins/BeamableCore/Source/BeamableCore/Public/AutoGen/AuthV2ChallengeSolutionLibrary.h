#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2ChallengeSolution.h"

#include "AuthV2ChallengeSolutionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2ChallengeSolutionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2ChallengeSolution To JSON String")
	static FString AuthV2ChallengeSolutionToJsonString(const UAuthV2ChallengeSolution* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2ChallengeSolution", meta=(DefaultToSelf="Outer", AdvancedDisplay="ChallengeToken, Solution, Outer", NativeMakeFunc))
	static UAuthV2ChallengeSolution* Make(FOptionalString ChallengeToken, FOptionalString Solution, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2ChallengeSolution", meta=(NativeBreakFunc))
	static void Break(const UAuthV2ChallengeSolution* Serializable, FOptionalString& ChallengeToken, FOptionalString& Solution);
};