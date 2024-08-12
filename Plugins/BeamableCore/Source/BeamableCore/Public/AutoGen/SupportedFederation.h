#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Enums/FederationType.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalOptionalJsonNodeWrapper.h"

#include "SupportedFederation.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USupportedFederation : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EFederationType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name Space", Category="Beam")
	FOptionalString NameSpace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Settings", Category="Beam")
	FOptionalOptionalJsonNodeWrapper Settings = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};