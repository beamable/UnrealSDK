
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
		Serializer->WriteValue(TEXT("interfaceName"), InterfaceName);
		Serializer->WriteValue(TEXT("federationId"), FederationId);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("interfaceName"), InterfaceName);
		Serializer->WriteValue(TEXT("federationId"), FederationId);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		InterfaceName = Bag->GetStringField(TEXT("interfaceName"));
		FederationId = Bag->GetStringField(TEXT("federationId"));	
	}
};


