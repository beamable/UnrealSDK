
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "FederationEntryStreamData.generated.h"


UCLASS(BlueprintType)
class UFederationEntryStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString InterfaceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FederationId = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("interfaceName"), InterfaceName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("federationId"), FederationId, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("interfaceName"), InterfaceName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("federationId"), FederationId, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("interfaceName"), Bag, InterfaceName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("federationId"), Bag, FederationId);	
	}
};


