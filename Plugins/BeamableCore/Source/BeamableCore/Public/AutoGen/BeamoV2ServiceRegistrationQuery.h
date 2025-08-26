#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2SupportedFederation.h"

#include "BeamoV2ServiceRegistrationQuery.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2ServiceRegistrationQuery : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Local Only", Category="Beam")
	FOptionalBool bLocalOnly = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FOptionalString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Routing Key", Category="Beam")
	FOptionalString RoutingKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Federation", Category="Beam")
	FOptionalBeamoV2SupportedFederation Federation = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};