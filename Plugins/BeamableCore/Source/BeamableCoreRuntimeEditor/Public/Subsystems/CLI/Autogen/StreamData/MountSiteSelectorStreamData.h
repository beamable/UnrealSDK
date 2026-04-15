
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "MountSiteSelectorStreamData.generated.h"


UCLASS(BlueprintType)
class UMountSiteSelectorStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Selector = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("selector"), Selector, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("selector"), Selector, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("selector"), Bag, Selector);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("type"), Bag, Type);	
	}
};


