#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"


#include "ContextInfo.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContextInfo : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Platform", Category="Beam")
	FString Platform = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device", Category="Beam")
	FString Device = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};