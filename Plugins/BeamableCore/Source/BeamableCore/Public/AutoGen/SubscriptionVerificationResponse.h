
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "SubscriptionVerificationResponse.generated.h"

UCLASS(BlueprintType)
class USubscriptionVerificationResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Challenge")
	FString HubChallenge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Type")
	FString ContentType;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};