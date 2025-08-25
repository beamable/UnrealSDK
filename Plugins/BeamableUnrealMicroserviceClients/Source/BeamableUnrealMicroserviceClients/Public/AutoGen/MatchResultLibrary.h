#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MatchResult.h"

#include "MatchResultLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMatchResultLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Json", DisplayName="MatchResult To JSON String")
	static FString MatchResultToJsonString(const UMatchResult* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make MatchResult", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMatchResult* Make(TMap<FString, UPerPlayerMatchResult*> PerPlayerMatchResults, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Break MatchResult", meta=(NativeBreakFunc))
	static void Break(const UMatchResult* Serializable, TMap<FString, UPerPlayerMatchResult*>& PerPlayerMatchResults);
};