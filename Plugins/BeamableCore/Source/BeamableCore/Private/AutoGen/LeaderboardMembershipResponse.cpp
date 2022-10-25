
#include "AutoGen/LeaderboardMembershipResponse.h"



void ULeaderboardMembershipResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);
}

void ULeaderboardMembershipResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);		
}

void ULeaderboardMembershipResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bResult = Bag->GetBoolField(TEXT("result"));
}