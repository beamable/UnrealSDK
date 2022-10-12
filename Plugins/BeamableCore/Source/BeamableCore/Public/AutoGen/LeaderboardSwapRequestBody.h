
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "LeaderboardSwapRequestBody.generated.h"

UCLASS(BlueprintType)
class ULeaderboardSwapRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Winner Id")
	FOptionalInt64 WinnerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Loser Id")
	FOptionalInt64 LoserId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Swap Base")
	int64 SwapBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Delta")
	int64 Delta;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};