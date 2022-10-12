
#include "AutoGen/EventQueryResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UEventQueryResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEventObjectData*>(TEXT("events"), Events, Serializer);
}

void UEventQueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEventObjectData*>(TEXT("events"), Events, Serializer);		
}

void UEventQueryResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UEventObjectData*>(Bag->GetArrayField(TEXT("events")), Events, OuterOwner);
}