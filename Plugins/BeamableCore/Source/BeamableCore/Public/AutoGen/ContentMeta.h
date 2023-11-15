#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Enums/ContentVisibility.h"

#include "ContentMeta.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentMeta : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Visibility", Category="Beam")
	EContentVisibility Visibility = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Text", Category="Beam")
	FOptionalString Text = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Data", Category="Beam")
	FOptionalString Data = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};