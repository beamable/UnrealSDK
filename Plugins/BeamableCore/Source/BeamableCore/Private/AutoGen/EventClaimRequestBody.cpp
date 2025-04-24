
#include "BeamableCore/Public/AutoGen/EventClaimRequestBody.h"





void UEventClaimRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("eventId"), EventId, Serializer);
}

void UEventClaimRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("eventId"), EventId, Serializer);		
}

void UEventClaimRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("eventId")), EventId);
}



