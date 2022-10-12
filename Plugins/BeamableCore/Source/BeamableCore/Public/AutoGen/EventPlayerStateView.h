
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/EventPlayerPhaseView.h"
#include "AutoGen/Optionals/OptionalEventPlayerPhaseView.h"
#include "AutoGen/EventRewardState.h"
#include "AutoGen/Optionals/OptionalEventPlayerGroupState.h"

#include "EventPlayerStateView.generated.h"

UCLASS(BlueprintType)
class UEventPlayerStateView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Running")
	bool bRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="All Phases")
	TArray<UEventPlayerPhaseView*> AllPhases;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank")
	int64 Rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score")
	double Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Current Phase")
	FOptionalEventPlayerPhaseView CurrentPhase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remaining")
	int64 SecondsRemaining;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leaderboard Id")
	FString LeaderboardId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank Rewards")
	TArray<UEventRewardState*> RankRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Rewards")
	FOptionalEventPlayerGroupState GroupRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Rewards")
	TArray<UEventRewardState*> ScoreRewards;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};