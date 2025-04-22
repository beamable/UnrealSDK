
#include "BeamableCore/Public/AutoGen/LeaderboardGetRanksRequestBody.h"





void ULeaderboardGetRanksRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("ids"), Ids, Serializer);
}

void ULeaderboardGetRanksRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("ids"), Ids, Serializer);		
}

void ULeaderboardGetRanksRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ids")), Ids);
}



