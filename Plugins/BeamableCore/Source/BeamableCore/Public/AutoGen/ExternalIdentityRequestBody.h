
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalChallengeSolution.h"

#include "ExternalIdentityRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UExternalIdentityRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Address", Category="Beam")
	FString ProviderAddress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External Token", Category="Beam")
	FString ExternalToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Challenge Solution", Category="Beam")
	FOptionalChallengeSolution ChallengeSolution;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};