#pragma once

#include "BeamBackend/SemanticTypes/BeamCid.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamJsonUtilsMocks.generated.h"

UCLASS()
class UMockIntJsonSerializable : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	int a;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue("a", a);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue("a", a);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		a = Bag->GetIntegerField(TEXT("a"));
	}
};

UCLASS()
class UMockNestedJsonSerializable : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<UMockIntJsonSerializable*> a;

	UPROPERTY()
	UMockIntJsonSerializable* b;

	UPROPERTY()
	TMap<FString, UMockIntJsonSerializable*> c;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray("a", a, Serializer);
		UBeamJsonUtils::SerializeUObject("b", b, Serializer);
		UBeamJsonUtils::SerializeMap("c", c, Serializer);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		UBeamJsonUtils::SerializeArray("a", a, Serializer);
		UBeamJsonUtils::SerializeUObject("b", b, Serializer);
		UBeamJsonUtils::SerializeMap("c", c, Serializer);
	}
	
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeArray<UMockIntJsonSerializable*>(Bag->GetArrayField(TEXT("a")), a, OuterOwner);
		UBeamJsonUtils::DeserializeUObject<UMockIntJsonSerializable*>("b", Bag, b, OuterOwner);
		UBeamJsonUtils::DeserializeMap<UMockIntJsonSerializable*>(Bag->GetObjectField(TEXT("c")), c, OuterOwner);
	}
};

struct FOptionalMockNestedJsonSerializable : FBeamOptional
{
	UMockNestedJsonSerializable* Val = nullptr;

	virtual const void* GetAddr() const override { return &Val; }

	virtual void Set(const void* Data) override
	{
		Val = *((UMockNestedJsonSerializable**)Data);
		IsSet = true;
	}
};

struct FOptionalMockNestedSemanticType : FBeamOptional
{
	FBeamCid Val;

	virtual const void* GetAddr() const override { return &Val; }

	virtual void Set(const void* Data) override
	{
		Val = *((FBeamCid*)Data);
		IsSet = true;
	}
};