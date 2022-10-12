
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalDouble.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "LeaderboardAddRequestBody.generated.h"

UCLASS(BlueprintType)
class ULeaderboardAddRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Score")
	FOptionalDouble MaxScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats")
	FOptionalMapOfString Stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score")
	double Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Min Score")
	FOptionalDouble MinScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	int64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Increment")
	FOptionalBool bIncrement;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};