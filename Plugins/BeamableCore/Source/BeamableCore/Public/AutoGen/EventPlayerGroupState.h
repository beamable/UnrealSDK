
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/EventRewardState.h"

#include "EventPlayerGroupState.generated.h"

UCLASS(BlueprintType)
class UEventPlayerGroupState : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Score")
	double GroupScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Id")
	FOptionalString GroupId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank Rewards")
	TArray<UEventRewardState*> RankRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Rank")
	int64 GroupRank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Rewards")
	TArray<UEventRewardState*> ScoreRewards;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};