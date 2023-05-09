#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardPlayerAssignmentRequestBody.h"

#include "LeaderboardPlayerAssignmentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardPlayerAssignmentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardPlayerAssignmentRequestBody To JSON String")
	static FString LeaderboardPlayerAssignmentRequestBodyToJsonString(const ULeaderboardPlayerAssignmentRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardPlayerAssignmentRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bJoinBoard, Outer", NativeMakeFunc))
	static ULeaderboardPlayerAssignmentRequestBody* Make(FString BoardId, FOptionalBool bJoinBoard, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardPlayerAssignmentRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardPlayerAssignmentRequestBody* Serializable, FString& BoardId, FOptionalBool& bJoinBoard);
};