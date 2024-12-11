
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
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteValue(TEXT("createdAt"), CreatedAt);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("id"), Id);
		Serializer->WriteValue(TEXT("checksum"), Checksum);
		Serializer->WriteValue(TEXT("createdAt"), CreatedAt);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Id = Bag->GetStringField(TEXT("id"));
		Checksum = Bag->GetStringField(TEXT("checksum"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("createdAt")), CreatedAt);	
	}
};


