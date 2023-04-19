
#include "BeamableCore/Public/AutoGen/EventApplyRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UEventApplyRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UEvent*>("content", Content, Serializer);
}

void UEventApplyRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UEvent*>("content", Content, Serializer);		
}

void UEventApplyRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UEvent*>("content", Bag, Content, OuterOwner);
}



