
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
		Serializer->WriteValue(TEXT("name"), Name);
		Serializer->WriteValue(TEXT("projPath"), ProjPath);
		Serializer->WriteValue(TEXT("dllName"), DllName);
		Serializer->WriteValue(TEXT("type"), Type);	
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("name"), Name);
		Serializer->WriteValue(TEXT("projPath"), ProjPath);
		Serializer->WriteValue(TEXT("dllName"), DllName);
		Serializer->WriteValue(TEXT("type"), Type);	
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		Name = Bag->GetStringField(TEXT("name"));
		ProjPath = Bag->GetStringField(TEXT("projPath"));
		DllName = Bag->GetStringField(TEXT("dllName"));
		Type = Bag->GetStringField(TEXT("type"));	
	}
};


