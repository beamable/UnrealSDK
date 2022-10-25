
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"


#include "SubscriptionVerificationResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USubscriptionVerificationResponse : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Challenge", Category="Beam")
	FString HubChallenge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Type", Category="Beam")
	FString ContentType;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};