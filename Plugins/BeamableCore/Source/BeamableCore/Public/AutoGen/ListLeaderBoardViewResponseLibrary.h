#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListLeaderBoardViewResponse.h"

#include "ListLeaderBoardViewResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListLeaderBoardViewResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="ListLeaderBoardViewResponse To JSON String")
	static FString ListLeaderBoardViewResponseToJsonString(const UListLeaderBoardViewResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make ListLeaderBoardViewResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListLeaderBoardViewResponse* Make(FString Result, TArray<ULeaderBoardView*> Lbs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break ListLeaderBoardViewResponse", meta=(NativeBreakFunc))
	static void Break(const UListLeaderBoardViewResponse* Serializable, FString& Result, TArray<ULeaderBoardView*>& Lbs);
};