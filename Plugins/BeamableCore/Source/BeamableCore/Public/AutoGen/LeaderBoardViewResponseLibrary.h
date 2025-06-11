#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponse.h"

#include "LeaderBoardViewResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderBoardViewResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderBoardViewResponse To JSON String")
	static FString LeaderBoardViewResponseToJsonString(const ULeaderBoardViewResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderBoardViewResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaderBoardViewResponse* Make(FString Result, ULeaderBoardView* Lb, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderBoardViewResponse", meta=(NativeBreakFunc))
	static void Break(const ULeaderBoardViewResponse* Serializable, FString& Result, ULeaderBoardView*& Lb);
};