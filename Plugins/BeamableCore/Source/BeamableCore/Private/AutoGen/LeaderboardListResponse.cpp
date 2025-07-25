
#include "BeamableCore/Public/AutoGen/LeaderboardListResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void ULeaderboardListResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULeaderboardListResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("total"), Total, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offset"), Offset, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("nameList"), NameList, Serializer);
}

void ULeaderboardListResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("total"), Total, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offset"), Offset, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("nameList"), NameList, Serializer);		
}

void ULeaderboardListResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("total"), Bag, Total);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("offset"), Bag, Offset);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("nameList"), Bag, NameList, OuterOwner);
}



