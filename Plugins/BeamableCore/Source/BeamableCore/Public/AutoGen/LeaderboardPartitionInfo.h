
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "LeaderboardPartitionInfo.generated.h"

UCLASS(BlueprintType)
class ULeaderboardPartitionInfo : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	int64 PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leaderboard Id")
	FString LeaderboardId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Empty")
	bool bIsEmpty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Partition")
	FOptionalInt32 Partition;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};