
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/TournamentCurrencyReward.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "PlayerStatus.generated.h"

UCLASS(BlueprintType)
class UPlayerStatus : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Last Update Cycle")
	int32 LastUpdateCycle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id")
	FString TournamentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stage")
	int32 Stage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Unclaimed Rewards")
	TArray<UTournamentCurrencyReward*> UnclaimedRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tier")
	int32 Tier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Id")
	FOptionalInt64 GroupId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	int64 PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id")
	FString ContentId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};