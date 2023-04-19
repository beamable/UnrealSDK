
#include "BeamableCore/Public/AutoGen/Maps/MapOfString.h"
#include "Serialization/BeamJsonUtils.h"

FMapOfString::FMapOfString() = default;

FMapOfString::FMapOfString(const TMap<FString, FString>& Val): Values(Val)
{}

void FMapOfString::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(Values, Serializer);
}

void FMapOfString::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(Values, Serializer);
}

void FMapOfString::BeamDeserializeElements(const TSharedPtr<FJsonObject>& Elements)
{
	UBeamJsonUtils::DeserializeMap<FString>(Elements, Values);
}