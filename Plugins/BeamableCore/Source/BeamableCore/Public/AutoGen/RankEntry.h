
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfRankEntryStat.h"
#include "AutoGen/Optionals/OptionalDouble.h"

#include "RankEntry.generated.h"

UCLASS(BlueprintType)
class URankEntry : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats")
	FOptionalArrayOfRankEntryStat Stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank")
	int64 Rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score")
	FOptionalDouble Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Columns")
	TMap<FString, int64> Columns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gt")
	int64 Gt;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};