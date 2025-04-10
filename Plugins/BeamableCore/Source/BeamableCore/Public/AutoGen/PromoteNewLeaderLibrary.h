#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PromoteNewLeader.h"

#include "PromoteNewLeaderLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPromoteNewLeaderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Json", DisplayName="PromoteNewLeader To JSON String")
	static FString PromoteNewLeaderToJsonString(const UPromoteNewLeader* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Make PromoteNewLeader", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Outer", NativeMakeFunc))
	static UPromoteNewLeader* Make(FOptionalBeamGamerTag PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Break PromoteNewLeader", meta=(NativeBreakFunc))
	static void Break(const UPromoteNewLeader* Serializable, FOptionalBeamGamerTag& PlayerId);
};