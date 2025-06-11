#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerId.h"

#include "PlayerIdLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerIdLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Json", DisplayName="PlayerId To JSON String")
	static FString PlayerIdToJsonString(const UPlayerId* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make PlayerId", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPlayerId* Make(FBeamGamerTag PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Break PlayerId", meta=(NativeBreakFunc))
	static void Break(const UPlayerId* Serializable, FBeamGamerTag& PlayerId);
};