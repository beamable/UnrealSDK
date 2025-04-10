#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardView.h"

#include "LeaderBoardViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderBoardViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderBoardView To JSON String")
	static FString LeaderBoardViewToJsonString(const ULeaderBoardView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderBoardView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Rankgt, Outer", NativeMakeFunc))
	static ULeaderBoardView* Make(FString LbId, int64 BoardSize, TArray<URankEntry*> Rankings, FOptionalRankEntry Rankgt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderBoardView", meta=(NativeBreakFunc))
	static void Break(const ULeaderBoardView* Serializable, FString& LbId, int64& BoardSize, TArray<URankEntry*>& Rankings, FOptionalRankEntry& Rankgt);
};