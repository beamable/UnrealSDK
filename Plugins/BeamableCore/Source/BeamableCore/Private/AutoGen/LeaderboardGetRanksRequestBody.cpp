
#include "BeamableCore/Public/AutoGen/LeaderboardGetRanksRequestBody.h"





void ULeaderboardGetRanksRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("ids"), Ids);
}

void ULeaderboardGetRanksRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("ids"), Ids);		
}

void ULeaderboardGetRanksRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Ids = Bag->GetStringField(TEXT("ids"));
}



