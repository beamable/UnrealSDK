#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PromoteNewLeader.h"

#include "PromoteNewLeaderLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPromoteNewLeaderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PromoteNewLeader To JSON String")
	static FString PromoteNewLeaderToJsonString(const UPromoteNewLeader* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PromoteNewLeader", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Outer", NativeMakeFunc))
	static UPromoteNewLeader* Make(FOptionalString PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PromoteNewLeader", meta=(NativeBreakFunc))
	static void Break(const UPromoteNewLeader* Serializable, FOptionalString& PlayerId);
};