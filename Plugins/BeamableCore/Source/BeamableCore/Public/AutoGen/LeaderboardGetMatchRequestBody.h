#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "LeaderboardGetMatchRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API ULeaderboardGetMatchRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pool Size", Category="Beam")
	int32 PoolSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Windows", Category="Beam")
	int32 Windows = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Window Size", Category="Beam")
	int32 WindowSize = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};