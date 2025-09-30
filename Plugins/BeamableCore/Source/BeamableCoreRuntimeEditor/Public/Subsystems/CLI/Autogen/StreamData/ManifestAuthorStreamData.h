
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ManifestAuthorStreamData.generated.h"


UCLASS(BlueprintType)
class UManifestAuthorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Email = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 AccountId = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Email"), Email, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AccountId"), AccountId, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Email"), Email, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AccountId"), AccountId, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Email"), Bag, Email);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("AccountId"), Bag, AccountId);	
	}
};


