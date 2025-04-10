#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerStatusUpdate.h"

#include "PlayerStatusUpdateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerStatusUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|4 - Json", DisplayName="PlayerStatusUpdate To JSON String")
	static FString PlayerStatusUpdateToJsonString(const UPlayerStatusUpdate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|3 - Backend", DisplayName="Make PlayerStatusUpdate", meta=(DefaultToSelf="Outer", AdvancedDisplay="Tier, Stage, Score, Outer", NativeMakeFunc))
	static UPlayerStatusUpdate* Make(FOptionalInt32 Tier, FOptionalInt32 Stage, FOptionalDouble Score, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|3 - Backend", DisplayName="Break PlayerStatusUpdate", meta=(NativeBreakFunc))
	static void Break(const UPlayerStatusUpdate* Serializable, FOptionalInt32& Tier, FOptionalInt32& Stage, FOptionalDouble& Score);
};