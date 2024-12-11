
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


