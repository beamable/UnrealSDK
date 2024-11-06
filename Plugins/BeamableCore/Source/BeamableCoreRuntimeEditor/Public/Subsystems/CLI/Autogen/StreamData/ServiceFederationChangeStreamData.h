
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ServiceFederationChangeStreamData.generated.h"


UCLASS()
class UServiceFederationChangeStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Service = {};
	UPROPERTY()
	FString FederationId = {};
	UPROPERTY()
	FString FederationInterface = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("federationId"), FederationId);
		Serializer->WriteValue(TEXT("federationInterface"), FederationInterface);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("service"), Service);
		Serializer->WriteValue(TEXT("federationId"), FederationId);
		Serializer->WriteValue(TEXT("federationInterface"), FederationInterface);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Service = Bag->GetStringField(TEXT("service"));
		FederationId = Bag->GetStringField(TEXT("federationId"));
		FederationInterface = Bag->GetStringField(TEXT("federationInterface"));	
	}
};


