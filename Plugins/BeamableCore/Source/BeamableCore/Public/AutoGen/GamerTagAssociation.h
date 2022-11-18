
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"


#include "GamerTagAssociation.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGamerTagAssociation : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Project Id", Category="Beam")
	FString ProjectId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag", Category="Beam")
	int64 GamerTag;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};