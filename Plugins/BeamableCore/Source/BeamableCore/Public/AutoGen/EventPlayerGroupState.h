#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/EventRewardState.h"

#include "EventPlayerGroupState.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UEventPlayerGroupState : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Score", Category="Beam")
	double GroupScore = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Rank", Category="Beam")
	int64 GroupRank = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank Rewards", Category="Beam")
	TArray<UEventRewardState*> RankRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score Rewards", Category="Beam")
	TArray<UEventRewardState*> ScoreRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Id", Category="Beam")
	FOptionalString GroupId = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};