
#pragma once


#include "Serialization/BeamJsonUtils.h"
#include "DependencyDataStreamData.generated.h"


UCLASS(BlueprintType)
class UDependencyDataStreamData : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProjPath = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DllName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type = {};

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("projPath"), ProjPath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("dllName"), DllName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("projPath"), ProjPath, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("dllName"), DllName, Serializer);
		UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("projPath")), ProjPath);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("dllName")), DllName);
		UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);	
	}
};


