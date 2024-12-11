
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "ServiceInfoStreamData.generated.h"


UCLASS(BlueprintType)
class UServiceInfoStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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


