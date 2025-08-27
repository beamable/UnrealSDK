#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoLimits.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalContentLimits.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalGatewayLimits.h"

#include "ServiceLimits.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UServiceLimits : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Beamo", Category="Beam")
	FOptionalBeamoLimits Beamo = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content", Category="Beam")
	FOptionalContentLimits Content = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gateway", Category="Beam")
	FOptionalGatewayLimits Gateway = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};