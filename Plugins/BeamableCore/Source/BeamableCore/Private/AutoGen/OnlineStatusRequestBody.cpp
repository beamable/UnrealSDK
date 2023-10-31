
#include "BeamableCore/Public/AutoGen/OnlineStatusRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UOnlineStatusRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerIds"), PlayerIds);
	Serializer->WriteValue(TEXT("intervalSecs"), IntervalSecs);
}

void UOnlineStatusRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerIds"), PlayerIds);
	Serializer->WriteValue(TEXT("intervalSecs"), IntervalSecs);		
}

void UOnlineStatusRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PlayerIds = Bag->GetStringField(TEXT("playerIds"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("intervalSecs")), IntervalSecs);
}



