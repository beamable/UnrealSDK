#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfSupportedFederation.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "ServiceRegistrationRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UServiceRegistrationRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Routing Key", Category="Beam")
	FOptionalString RoutingKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Traffic Filter Enabled", Category="Beam")
	FOptionalBool bTrafficFilterEnabled = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Federation", Category="Beam")
	FOptionalArrayOfSupportedFederation Federation = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};