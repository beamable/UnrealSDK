
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "UnityAssemblyReferenceDataStreamData.generated.h"


UCLASS(BlueprintType)
class UUnityAssemblyReferenceDataStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Path = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AssemblyName = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Path"), Path, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AssemblyName"), AssemblyName, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("Path"), Path, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("AssemblyName"), AssemblyName, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Path")), Path);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("AssemblyName")), AssemblyName);	
	}
};


