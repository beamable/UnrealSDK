
#include "BeamableCore/Public/AutoGen/EventClaimRequestBody.h"





void UEventClaimRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("eventId"), EventId);
}

void UEventClaimRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("eventId"), EventId);		
}

void UEventClaimRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	EventId = Bag->GetStringField(TEXT("eventId"));
}



