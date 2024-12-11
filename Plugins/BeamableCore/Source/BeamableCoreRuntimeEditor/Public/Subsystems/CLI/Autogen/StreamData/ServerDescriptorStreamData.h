
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ServerDescriptorStreamData.generated.h"


UCLASS(BlueprintType)
class UServerDescriptorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Port = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 InflightRequests = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Url = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Owner = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Version = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("port"), Port);
		Serializer->WriteValue(TEXT("pid"), Pid);
		Serializer->WriteValue(TEXT("inflightRequests"), InflightRequests);
		Serializer->WriteValue(TEXT("url"), Url);
		Serializer->WriteValue(TEXT("owner"), Owner);
		Serializer->WriteValue(TEXT("version"), Version);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("port"), Port);
		Serializer->WriteValue(TEXT("pid"), Pid);
		Serializer->WriteValue(TEXT("inflightRequests"), InflightRequests);
		Serializer->WriteValue(TEXT("url"), Url);
		Serializer->WriteValue(TEXT("owner"), Owner);
		Serializer->WriteValue(TEXT("version"), Version);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Port = Bag->GetIntegerField(TEXT("port"));
		Pid = Bag->GetIntegerField(TEXT("pid"));
		FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("inflightRequests")), InflightRequests);
		Url = Bag->GetStringField(TEXT("url"));
		Owner = Bag->GetStringField(TEXT("owner"));
		Version = Bag->GetStringField(TEXT("version"));	
	}
};


