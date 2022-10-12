
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "ScoreRequestBody.generated.h"

UCLASS(BlueprintType)
class UScoreRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id")
	FString TournamentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats")
	FOptionalMapOfString Stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score")
	double Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	int64 PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Increment")
	FOptionalBool bIncrement;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};