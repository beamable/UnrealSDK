#include "Serialization/BeamJsonSerializable.h"
FBeamJsonSerializable::~FBeamJsonSerializable() = default;

void FBeamJsonSerializable::BeamSerialize(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteObjectStart();
	BeamSerializeProperties(Serializer);
	Serializer->WriteObjectEnd();
}

void FBeamJsonSerializable::BeamSerialize(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteObjectStart();
	BeamSerializeProperties(Serializer);
	Serializer->WriteObjectEnd();
}

void FBeamJsonSerializable::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	ensure(false);
}

void FBeamJsonSerializable::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	ensure(false);
}

void FBeamJsonSerializable::BeamDeserialize(const FString& JsonString)
{
	auto Bag = FJsonDataBag{};
	Bag.FromJson(JsonString);
	BeamDeserializeProperties(Bag.JsonObject);
}

void FBeamJsonSerializable::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ensure(false);
}
