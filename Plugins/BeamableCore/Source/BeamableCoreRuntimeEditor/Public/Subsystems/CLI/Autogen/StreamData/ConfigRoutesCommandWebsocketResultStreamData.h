
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ConfigRoutesCommandWebsocketResultStreamData.generated.h"


UCLASS(BlueprintType)
class UConfigRoutesCommandWebsocketResultStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Uri = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Provider = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("provider"), Provider, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("provider"), Provider, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("uri"), Bag, Uri);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("provider"), Bag, Provider);	
	}
};


