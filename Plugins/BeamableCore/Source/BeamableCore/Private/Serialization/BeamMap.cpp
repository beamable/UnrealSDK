#include "Serialization/BeamMap.h"

#include "Serialization/BeamJsonUtils.h"

void FBeamMap::BeamSerialize(TUnrealJsonSerializer& Serializer) const
{
	// For the map case, we simply serialize the map as the entire object --- if we try to wrap it around, we'd get
	// {
	//    { ... Map contents ... }
	// }
	// which is invalid JSON.
	BeamSerializeProperties(Serializer);
}

void FBeamMap::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	ensure(false); // "This should be overriden!"
}

void FBeamMap::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	ensure(false); // "This should be overriden!"
}

void FBeamMap::BeamDeserialize(const FString& JsonString)
{
	FJsonDataBag Bag;
	UBeamJsonUtils::FromJsonToBag(JsonString, Bag);
	BeamDeserializeElements(Bag.JsonObject);
}

void FBeamMap::BeamDeserializeElements(const TSharedPtr<FJsonObject>& Bag)
{
	ensure(false); // "This should be overriden!"
}

void FBeamMap::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ensure(false); // "This should never be called!"
}
