
#include "BeamableCore/Public/AutoGen/Maps/MapOfInt32.h"
#include "Serialization/BeamJsonUtils.h"

FMapOfInt32::FMapOfInt32() = default;

FMapOfInt32::FMapOfInt32(const TMap<FString, int32>& Val): Values(Val)
{}

void FMapOfInt32::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<int32>(Values, Serializer);
}

void FMapOfInt32::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<int32>(Values, Serializer);
}

void FMapOfInt32::BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements)
{
	UBeamJsonUtils::DeserializeMap<int32>(Elements, Values);
}