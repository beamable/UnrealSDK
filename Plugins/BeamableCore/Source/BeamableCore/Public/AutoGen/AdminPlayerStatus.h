
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/TournamentCurrencyReward.h"

#include "AdminPlayerStatus.generated.h"

UCLASS(BlueprintType)
class UAdminPlayerStatus : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id")
	FString TournamentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stage")
	int32 Stage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Unclaimed Rewards")
	TArray<UTournamentCurrencyReward*> UnclaimedRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tier")
	int32 Tier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank")
	int32 Rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score")
	double Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	int64 PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id")
	FString ContentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Next Cycle Start Ms")
	int64 NextCycleStartMs;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};