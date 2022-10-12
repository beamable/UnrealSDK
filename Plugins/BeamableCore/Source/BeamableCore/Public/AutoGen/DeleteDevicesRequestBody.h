
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"

#include "DeleteDevicesRequestBody.generated.h"

UCLASS(BlueprintType)
class UDeleteDevicesRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Ids")
	FOptionalArrayOfString DeviceIds;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};