#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PerPlayerMatchResult.h"

#include "PerPlayerMatchResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UPerPlayerMatchResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Json", DisplayName="PerPlayerMatchResult To JSON String")
	static FString PerPlayerMatchResultToJsonString(const UPerPlayerMatchResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make PerPlayerMatchResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPerPlayerMatchResult* Make(bool bWon, int32 RankEarned, int32 CoinsEarned, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Break PerPlayerMatchResult", meta=(NativeBreakFunc))
	static void Break(const UPerPlayerMatchResult* Serializable, bool& bWon, int32& RankEarned, int32& CoinsEarned);
};