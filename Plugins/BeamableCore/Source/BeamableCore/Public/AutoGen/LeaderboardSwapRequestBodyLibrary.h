#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardSwapRequestBody.h"

#include "LeaderboardSwapRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardSwapRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardSwapRequestBody To JSON String")
	static FString LeaderboardSwapRequestBodyToJsonString(const ULeaderboardSwapRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardSwapRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="WinnerId, LoserId, Outer", NativeMakeFunc))
	static ULeaderboardSwapRequestBody* Make(int64 SwapBase, int64 Delta, FOptionalInt64 WinnerId, FOptionalInt64 LoserId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardSwapRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardSwapRequestBody* Serializable, int64& SwapBase, int64& Delta, FOptionalInt64& WinnerId, FOptionalInt64& LoserId);
};