#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/TournamentCurrencyReward.h"

#include "TournamentEntry.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UTournamentEntry : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stage", Category="Beam")
	int32 Stage = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tier", Category="Beam")
	int32 Tier = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank", Category="Beam")
	int64 Rank = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score", Category="Beam")
	double Score = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	int64 PlayerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stage Change", Category="Beam")
	int32 StageChange = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Currency Rewards", Category="Beam")
	TArray<UTournamentCurrencyReward*> CurrencyRewards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Previous Stage Change", Category="Beam")
	FOptionalInt32 PreviousStageChange = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Next Stage Change", Category="Beam")
	FOptionalInt32 NextStageChange = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};