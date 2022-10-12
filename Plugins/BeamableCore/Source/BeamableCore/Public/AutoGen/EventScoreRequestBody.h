
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"

#include "EventScoreRequestBody.generated.h"

UCLASS(BlueprintType)
class UEventScoreRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Event Id")
	FString EventId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score")
	double Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Increment")
	FOptionalBool bIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats")
	FOptionalMapOfString Stats;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};