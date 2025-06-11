#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaderboardDetails.h"

#include "LeaderboardDetailsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaderboardDetailsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Json", DisplayName="LeaderboardDetails To JSON String")
	static FString LeaderboardDetailsToJsonString(const ULeaderboardDetails* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make LeaderboardDetails", meta=(DefaultToSelf="Outer", AdvancedDisplay="Orules, MetaData, Outer", NativeMakeFunc))
	static ULeaderboardDetails* Make(FString Lbid, int32 NumberOfEntries, FString FullName, ULeaderBoardView* View, FOptionalOrderRules Orules, FOptionalMetadataView MetaData, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Break LeaderboardDetails", meta=(NativeBreakFunc))
	static void Break(const ULeaderboardDetails* Serializable, FString& Lbid, int32& NumberOfEntries, FString& FullName, ULeaderBoardView*& View, FOptionalOrderRules& Orules, FOptionalMetadataView& MetaData);
};