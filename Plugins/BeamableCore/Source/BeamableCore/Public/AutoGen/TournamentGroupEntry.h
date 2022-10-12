
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/TournamentCurrencyReward.h"

#include "TournamentGroupEntry.generated.h"

UCLASS(BlueprintType)
class UTournamentGroupEntry : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank")
	int64 Rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score")
	double Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency Rewards")
	TArray<UTournamentCurrencyReward*> CurrencyRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Id")
	int64 GroupId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stage Change")
	int32 StageChange;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};