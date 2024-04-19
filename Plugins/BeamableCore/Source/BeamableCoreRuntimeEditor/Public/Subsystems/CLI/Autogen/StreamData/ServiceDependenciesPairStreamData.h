
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/DependencyDataStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServiceDependenciesPairStreamData.generated.h"


UCLASS()
class UServiceDependenciesPairStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Name = {};
	UPROPERTY()
	TArray<UDependencyDataStreamData*> Dependencies = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		UBeamJsonUtils::SerializeArray<UDependencyDataStreamData*>(TEXT("dependencies"), Dependencies, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		UBeamJsonUtils::SerializeArray<UDependencyDataStreamData*>(TEXT("dependencies"), Dependencies, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Name = Bag->GetStringField(TEXT("name"));
		UBeamJsonUtils::DeserializeArray<UDependencyDataStreamData*>(Bag->GetArrayField(TEXT("dependencies")), Dependencies, OuterOwner);	
	}
};


