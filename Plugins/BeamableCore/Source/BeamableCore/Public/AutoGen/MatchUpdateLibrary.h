
#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MatchUpdate.h"

#include "MatchUpdateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMatchUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MatchUpdate To JSON String")
	static FString MatchUpdateToJsonString(const UMatchUpdate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MatchUpdate", meta=(DefaultToSelf="Outer", AdvancedDisplay="SecondsRemaining, Outer", NativeMakeFunc))
	static UMatchUpdate* Make(FString Game, bool bGameStarted, bool bMinPlayersReached, TArray<int64> Players, FOptionalInt64 SecondsRemaining, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MatchUpdate", meta=(NativeBreakFunc))
	static void Break(const UMatchUpdate* Serializable, FString& Game, bool& bGameStarted, bool& bMinPlayersReached, TArray<int64>& Players, FOptionalInt64& SecondsRemaining);
};