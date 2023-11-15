#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"


#include "StatStringListEntry.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatStringListEntry : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="K", Category="Beam")
	FString K = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="V", Category="Beam")
	FString V = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};