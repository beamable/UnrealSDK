
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "RunningFederationStreamData.generated.h"


UCLASS()
class URunningFederationStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString NameSpace = {};
	UPROPERTY()
	FString FederationType = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("nameSpace"), NameSpace);
		Serializer->WriteValue(TEXT("federationType"), FederationType);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("nameSpace"), NameSpace);
		Serializer->WriteValue(TEXT("federationType"), FederationType);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		NameSpace = Bag->GetStringField(TEXT("nameSpace"));
		FederationType = Bag->GetStringField(TEXT("federationType"));	
	}
};


