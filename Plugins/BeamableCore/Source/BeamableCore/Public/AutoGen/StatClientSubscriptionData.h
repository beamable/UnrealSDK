#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"


#include "StatClientSubscriptionData.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatClientSubscriptionData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Target Gamer Tag", Category="Beam")
	int64 TargetGamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Keys", Category="Beam")
	TArray<FString> Keys = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};