
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ManifestProjectDataStreamData.generated.h"


UCLASS(BlueprintType)
class UManifestProjectDataStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PID = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RealmName = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PID"), PID, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RealmName"), RealmName, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("PID"), PID, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("RealmName"), RealmName, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("PID"), Bag, PID);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("RealmName"), Bag, RealmName);	
	}
};


