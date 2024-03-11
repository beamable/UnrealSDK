
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ServiceInfoStreamData.generated.h"


UCLASS()
class UServiceInfoStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Name = {};
	UPROPERTY()
	FString ProjectPath = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		Serializer->WriteValue(TEXT("projectPath"), ProjectPath);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		Serializer->WriteValue(TEXT("projectPath"), ProjectPath);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Name = Bag->GetStringField(TEXT("name"));
		ProjectPath = Bag->GetStringField(TEXT("projectPath"));	
	}
};


