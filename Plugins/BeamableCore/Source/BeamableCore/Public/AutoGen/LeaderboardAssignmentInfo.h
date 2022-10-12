
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "LeaderboardAssignmentInfo.generated.h"

UCLASS(BlueprintType)
class ULeaderboardAssignmentInfo : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	int64 PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leaderboard Id")
	FString LeaderboardId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};