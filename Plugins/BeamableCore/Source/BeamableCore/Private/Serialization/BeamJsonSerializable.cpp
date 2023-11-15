#include "Serialization/BeamJsonSerializable.h"
FBeamJsonSerializableUStruct::~FBeamJsonSerializableUStruct() = default;

void FBeamJsonSerializableUStruct::BeamSerialize(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteObjectStart();
	BeamSerializeProperties(Serializer);
	Serializer->WriteObjectEnd();
}

void FBeamJsonSerializableUStruct::BeamSerialize(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteObjectStart();
	BeamSerializeProperties(Serializer);
	Serializer->WriteObjectEnd();
}

void FBeamJsonSerializableUStruct::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	ensure(false);
}

void FBeamJsonSerializableUStruct::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	ensure(false);
}

void FBeamJsonSerializableUStruct::BeamDeserialize(const FString& JsonString)
{
	auto Bag = FJsonDataBag{};
	Bag.FromJson(JsonString);
	BeamDeserializeProperties(Bag.JsonObject);
}

void FBeamJsonSerializableUStruct::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ensure(false);
}

void IBeamJsonSerializableUObject::BeamSerialize(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteObjectStart();
	BeamSerializeProperties(Serializer);
	Serializer->WriteObjectEnd();
}

void IBeamJsonSerializableUObject::BeamSerialize(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteObjectStart();
	BeamSerializeProperties(Serializer);
	Serializer->WriteObjectEnd();
}

void IBeamJsonSerializableUObject::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	ensure(false);
}

void IBeamJsonSerializableUObject::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	ensure(false);
}

void IBeamJsonSerializableUObject::BeamDeserialize(const FString& JsonString)
{
	auto Bag = FJsonDataBag{};
	Bag.FromJson(JsonString);
	BeamDeserializeProperties(Bag.JsonObject);
}

void IBeamJsonSerializableUObject::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ensure(false);
}
