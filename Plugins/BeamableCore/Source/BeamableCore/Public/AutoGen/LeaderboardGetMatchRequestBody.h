
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "LeaderboardGetMatchRequestBody.generated.h"

UCLASS(BlueprintType)
class ULeaderboardGetMatchRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pool Size")
	int32 PoolSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Windows")
	int32 Windows;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Window Size")
	int32 WindowSize;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};