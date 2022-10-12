
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalBeamoLimits.h"
#include "AutoGen/Optionals/OptionalContentLimits.h"
#include "AutoGen/Optionals/OptionalGatewayLimits.h"

#include "ServiceLimits.generated.h"

UCLASS(BlueprintType)
class UServiceLimits : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Beamo")
	FOptionalBeamoLimits Beamo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content")
	FOptionalContentLimits Content;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gateway")
	FOptionalGatewayLimits Gateway;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};