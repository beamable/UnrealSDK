
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "ObjectMetadataResponse.generated.h"

UCLASS(BlueprintType)
class UObjectMetadataResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Key")
	FString ObjectKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Metadata")
	TMap<FString, FString> Metadata;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};