#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardPlayerRequestBody.h"

#include "LeaderboardPlayerRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardPlayerRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardPlayerRequestBody To JSON String")
	static FString LeaderboardPlayerRequestBodyToJsonString(const ULeaderboardPlayerRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardPlayerRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardPlayerRequestBody* Make(int64 Dbid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardPlayerRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardPlayerRequestBody* Serializable, int64& Dbid);
};