
#include "BeamableCore/Public/AutoGen/Maps/MapOfContentMeta.h"
#include "Serialization/BeamJsonUtils.h"

FMapOfContentMeta::FMapOfContentMeta() = default;

FMapOfContentMeta::FMapOfContentMeta(const TMap<FString, UContentMeta*>& Val): Values(Val)
{}

void FMapOfContentMeta::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<UContentMeta*>(Values, Serializer);
}

void FMapOfContentMeta::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<UContentMeta*>(Values, Serializer);
}

void FMapOfContentMeta::BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements)
{
	UBeamJsonUtils::DeserializeMap<UContentMeta*>(Elements, Values);
}