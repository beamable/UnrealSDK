
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "CliServiceComponentStreamData.generated.h"


UCLASS(BlueprintType)
class UCliServiceComponentStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Name = Bag->GetStringField(TEXT("name"));	
	}
};


