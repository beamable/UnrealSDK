#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalOptionalJsonNodeWrapper.h"

#include "FederationInfo.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFederationInfo : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service", Category="Beam")
	FString Service = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Namespace", Category="Beam")
	FString Namespace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Settings", Category="Beam")
	FOptionalOptionalJsonNodeWrapper Settings = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};