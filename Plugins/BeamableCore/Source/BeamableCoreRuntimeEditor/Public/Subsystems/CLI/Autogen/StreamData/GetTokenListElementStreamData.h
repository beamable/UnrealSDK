
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "GetTokenListElementStreamData.generated.h"


UCLASS()
class UGetTokenListElementStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Created = {};
	UPROPERTY()
	FString Device = {};
	UPROPERTY()
	FString Platform = {};
	UPROPERTY()
	FString Token = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("created"), Created);
		Serializer->WriteValue(TEXT("device"), Device);
		Serializer->WriteValue(TEXT("platform"), Platform);
		Serializer->WriteValue(TEXT("token"), Token);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("created"), Created);
		Serializer->WriteValue(TEXT("device"), Device);
		Serializer->WriteValue(TEXT("platform"), Platform);
		Serializer->WriteValue(TEXT("token"), Token);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Created = Bag->GetStringField(TEXT("created"));
		Device = Bag->GetStringField(TEXT("device"));
		Platform = Bag->GetStringField(TEXT("platform"));
		Token = Bag->GetStringField(TEXT("token"));	
	}
};


