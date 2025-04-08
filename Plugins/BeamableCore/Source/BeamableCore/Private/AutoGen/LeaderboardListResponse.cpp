
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
	Serializer->WriteValue(TEXT("total"), Total);
	Serializer->WriteValue(TEXT("offset"), Offset);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("nameList"), NameList, Serializer);
}

void ULeaderboardListResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("total"), Total);
	Serializer->WriteValue(TEXT("offset"), Offset);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("nameList"), NameList, Serializer);		
}

void ULeaderboardListResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("total")), Total);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("offset")), Offset);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("nameList")), NameList, OuterOwner);
}



