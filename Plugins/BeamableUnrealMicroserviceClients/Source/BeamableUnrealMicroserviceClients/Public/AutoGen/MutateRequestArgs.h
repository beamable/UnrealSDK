#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutationInput.h"

#include "MutateRequestArgs.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UMutateRequestArgs : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Inputs", Category="Beam")
	TArray<UMutationInput*> Inputs = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};