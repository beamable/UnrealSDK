
#include "BeamableCore/Public/AutoGen/LeaderboardDetails.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void ULeaderboardDetails::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULeaderboardDetails::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lbid"), Lbid);
	Serializer->WriteValue(TEXT("numberOfEntries"), NumberOfEntries);
	Serializer->WriteValue(TEXT("fullName"), FullName);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("view", View, Serializer);
	UBeamJsonUtils::SerializeOptional<UOrderRules*>(TEXT("orules"), &Orules, Serializer);
	UBeamJsonUtils::SerializeOptional<UMetadataView*>(TEXT("metaData"), &MetaData, Serializer);
}

void ULeaderboardDetails::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lbid"), Lbid);
	Serializer->WriteValue(TEXT("numberOfEntries"), NumberOfEntries);
	Serializer->WriteValue(TEXT("fullName"), FullName);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("view", View, Serializer);
	UBeamJsonUtils::SerializeOptional<UOrderRules*>(TEXT("orules"), &Orules, Serializer);
	UBeamJsonUtils::SerializeOptional<UMetadataView*>(TEXT("metaData"), &MetaData, Serializer);		
}

void ULeaderboardDetails::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Lbid = Bag->GetStringField(TEXT("lbid"));
	NumberOfEntries = Bag->GetIntegerField(TEXT("numberOfEntries"));
	FullName = Bag->GetStringField(TEXT("fullName"));
	UBeamJsonUtils::DeserializeUObject<ULeaderBoardView*>("view", Bag, View, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UOrderRules*>("orules", Bag, Orules, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UMetadataView*>("metaData", Bag, MetaData, OuterOwner);
}



