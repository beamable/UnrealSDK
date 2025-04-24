
#include "BeamableCore/Public/AutoGen/OnlineStatusRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UOnlineStatusRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerIds"), PlayerIds, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("intervalSecs"), IntervalSecs, Serializer);
}

void UOnlineStatusRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerIds"), PlayerIds, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("intervalSecs"), IntervalSecs, Serializer);		
}

void UOnlineStatusRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerIds")), PlayerIds);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("intervalSecs")), IntervalSecs);
}



