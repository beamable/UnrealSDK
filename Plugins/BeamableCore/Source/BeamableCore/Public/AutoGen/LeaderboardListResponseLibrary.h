#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardListResponse.h"

#include "LeaderboardListResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardListResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaderboardListResponse To JSON String")
	static FString LeaderboardListResponseToJsonString(const ULeaderboardListResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaderboardListResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderboardListResponse* Make(int32 Total, int32 Offset, TArray<FString> NameList, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaderboardListResponse", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardListResponse* Serializable, int32& Total, int32& Offset, TArray<FString>& NameList);
};