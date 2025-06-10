#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "SubscriptionVerificationRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USubscriptionVerificationRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Mode", Category="Beam")
	FString HubMode = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Challenge", Category="Beam")
	FString HubChallenge = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Verify Token", Category="Beam")
	FString HubVerifyToken = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};