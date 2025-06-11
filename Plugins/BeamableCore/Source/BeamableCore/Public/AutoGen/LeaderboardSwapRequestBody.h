#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "Serialization/BeamJsonUtils.h"

#include "LeaderboardSwapRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API ULeaderboardSwapRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Swap Base", Category="Beam")
	int64 SwapBase = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Delta", Category="Beam")
	int64 Delta = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Winner Id", Category="Beam")
	FOptionalInt64 WinnerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Loser Id", Category="Beam")
	FOptionalInt64 LoserId = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};