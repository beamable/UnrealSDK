#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MatchType.h"

#include "MatchTypeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMatchTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MatchType To JSON String")
	static FString MatchTypeToJsonString(const UMatchType* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MatchType", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, WaitAfterMinReachedSecs, MaxWaitDurationSecs, MatchingIntervalSecs, Teams, Outer", NativeMakeFunc))
	static UMatchType* Make(FOptionalBeamContentId Id, FOptionalInt32 WaitAfterMinReachedSecs, FOptionalInt32 MaxWaitDurationSecs, FOptionalInt32 MatchingIntervalSecs, FOptionalArrayOfTeamContentProto Teams, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MatchType", meta=(NativeBreakFunc))
	static void Break(const UMatchType* Serializable, FOptionalBeamContentId& Id, FOptionalInt32& WaitAfterMinReachedSecs, FOptionalInt32& MaxWaitDurationSecs, FOptionalInt32& MatchingIntervalSecs, FOptionalArrayOfTeamContentProto& Teams);
};