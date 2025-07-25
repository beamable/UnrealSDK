
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ManifestChecksumStreamData.generated.h"


UCLASS(BlueprintType)
class UManifestChecksumStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Checksum = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 CreatedAt = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdAt"), CreatedAt, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdAt"), CreatedAt, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("checksum"), Bag, Checksum);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("createdAt"), Bag, CreatedAt);	
	}
};


