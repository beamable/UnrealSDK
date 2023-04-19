
#include "BeamableCore/Public/AutoGen/LeaderboardMembershipResponse.h"




void ULeaderboardMembershipResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULeaderboardMembershipResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);
}

void ULeaderboardMembershipResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), bResult);		
}

void ULeaderboardMembershipResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bResult = Bag->GetBoolField(TEXT("result"));
}



