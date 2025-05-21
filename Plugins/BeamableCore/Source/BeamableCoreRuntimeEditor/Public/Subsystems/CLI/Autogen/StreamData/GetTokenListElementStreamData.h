
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "GetTokenListElementStreamData.generated.h"


UCLASS(BlueprintType)
class UGetTokenListElementStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Device = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Platform = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Token = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("device"), Device, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("device"), Device, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("device")), Device);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("platform")), Platform);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("token")), Token);	
	}
};


