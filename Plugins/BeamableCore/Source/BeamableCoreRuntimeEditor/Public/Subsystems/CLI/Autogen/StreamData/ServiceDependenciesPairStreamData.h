
#pragma once

#include "Subsystems/CLI/Autogen/StreamData/DependencyDataStreamData.h"
#include "Serialization/BeamJsonUtils.h"
#include "ServiceDependenciesPairStreamData.generated.h"


UCLASS(BlueprintType)
class UServiceDependenciesPairStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDependencyDataStreamData*> Dependencies = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
		UBeamJsonUtils::SerializeArray<UDependencyDataStreamData*>(TEXT("dependencies"), Dependencies, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
		UBeamJsonUtils::SerializeArray<UDependencyDataStreamData*>(TEXT("dependencies"), Dependencies, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
		UBeamJsonUtils::DeserializeArray<UDependencyDataStreamData*>(Bag->GetArrayField(TEXT("dependencies")), Dependencies, OuterOwner);	
	}
};


