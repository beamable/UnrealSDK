#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "PerPlayerMatchResult.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UPerPlayerMatchResult : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Won", Category="Beam")
	bool bWon = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rank Earned", Category="Beam")
	int32 RankEarned = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Coins Earned", Category="Beam")
	int32 CoinsEarned = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};