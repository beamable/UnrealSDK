
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "SetEnabledCommandComponentStreamData.generated.h"


UCLASS(BlueprintType)
class USetEnabledCommandComponentStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Service = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Enabled = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("enabled"), Enabled);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("enabled"), Enabled);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		Enabled = Bag->GetStringField(TEXT("enabled"));	
	}
};


