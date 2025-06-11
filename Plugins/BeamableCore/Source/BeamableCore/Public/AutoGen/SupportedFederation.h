#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamFederationType.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Dom/JsonObject.h"

#include "SupportedFederation.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USupportedFederation : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EBeamFederationType Type = {};
	TSharedPtr<FJsonObject> Settings = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name Space", Category="Beam")
	FOptionalString NameSpace = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};