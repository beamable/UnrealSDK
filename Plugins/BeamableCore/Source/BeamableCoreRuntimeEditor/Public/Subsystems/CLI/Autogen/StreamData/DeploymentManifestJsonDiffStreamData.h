
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "DeploymentManifestJsonDiffStreamData.generated.h"


UCLASS()
class UDeploymentManifestJsonDiffStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString JsonPath = {};
	UPROPERTY()
	FString Type = {};
	UPROPERTY()
	FString CurrentValue = {};
	UPROPERTY()
	FString NextValue = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("jsonPath"), JsonPath);
		Serializer->WriteValue(TEXT("type"), Type);
		Serializer->WriteValue(TEXT("currentValue"), CurrentValue);
		Serializer->WriteValue(TEXT("nextValue"), NextValue);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("jsonPath"), JsonPath);
		Serializer->WriteValue(TEXT("type"), Type);
		Serializer->WriteValue(TEXT("currentValue"), CurrentValue);
		Serializer->WriteValue(TEXT("nextValue"), NextValue);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		JsonPath = Bag->GetStringField(TEXT("jsonPath"));
		Type = Bag->GetStringField(TEXT("type"));
		CurrentValue = Bag->GetStringField(TEXT("currentValue"));
		NextValue = Bag->GetStringField(TEXT("nextValue"));	
	}
};


