
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "FederationInstanceStreamData.generated.h"


UCLASS()
class UFederationInstanceStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString FederationId = {};
	UPROPERTY()
	TArray<FString> FederationTypes = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("FederationId"), FederationId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("FederationTypes"), FederationTypes, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("FederationId"), FederationId);
		UBeamJsonUtils::SerializeArray<FString>(TEXT("FederationTypes"), FederationTypes, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		FederationId = Bag->GetStringField(TEXT("FederationId"));
		UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("FederationTypes")), FederationTypes, OuterOwner);	
	}
};


