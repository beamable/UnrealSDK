
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "UnityAssemblyReferenceDataStreamData.generated.h"


UCLASS()
class UUnityAssemblyReferenceDataStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY()
	FString Path = {};
	UPROPERTY()
	FString AssemblyName = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Path"), Path);
		Serializer->WriteValue(TEXT("AssemblyName"), AssemblyName);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Path"), Path);
		Serializer->WriteValue(TEXT("AssemblyName"), AssemblyName);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Path = Bag->GetStringField(TEXT("Path"));
		AssemblyName = Bag->GetStringField(TEXT("AssemblyName"));	
	}
};


