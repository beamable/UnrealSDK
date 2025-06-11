
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
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectPath"), ProjectPath, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectPath"), ProjectPath, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("projectPath")), ProjectPath);	
	}
};


