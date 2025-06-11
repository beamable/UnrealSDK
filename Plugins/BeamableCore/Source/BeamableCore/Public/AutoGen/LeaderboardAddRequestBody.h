#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDouble.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "LeaderboardAddRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API ULeaderboardAddRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Score", Category="Beam")
	double Score = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	int64 Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Increment", Category="Beam")
	FOptionalBool bIncrement = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Score", Category="Beam")
	FOptionalDouble MaxScore = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Min Score", Category="Beam")
	FOptionalDouble MinScore = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats", Category="Beam")
	FOptionalMapOfString Stats = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};