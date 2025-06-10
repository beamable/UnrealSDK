#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/EventPlayerPhaseView.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventPlayerPhaseView.h"
#include "BeamableCore/Public/AutoGen/EventRewardState.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventPlayerGroupState.h"

#include "EventPlayerStateView.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UEventPlayerStateView : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Running", Category="Beam")
	bool bRunning = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank", Category="Beam")
	int64 Rank = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score", Category="Beam")
	double Score = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remaining", Category="Beam")
	int64 SecondsRemaining = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leaderboard Id", Category="Beam")
	FString LeaderboardId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="All Phases", Category="Beam")
	TArray<UEventPlayerPhaseView*> AllPhases = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank Rewards", Category="Beam")
	TArray<UEventRewardState*> RankRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Rewards", Category="Beam")
	TArray<UEventRewardState*> ScoreRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Current Phase", Category="Beam")
	FOptionalEventPlayerPhaseView CurrentPhase = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Rewards", Category="Beam")
	FOptionalEventPlayerGroupState GroupRewards = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};