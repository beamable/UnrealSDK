
#include "AutoGen/LeaderboardDetails.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void ULeaderboardDetails ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lbid"), Lbid);
	UBeamJsonUtils::SerializeOptional<UOrderRules*>(TEXT("orules"), &Orules, Serializer);
	Serializer->WriteValue(TEXT("numberOfEntries"), NumberOfEntries);
	Serializer->WriteValue(TEXT("fullName"), FullName);
	UBeamJsonUtils::SerializeOptional<UMetadataView*>(TEXT("metaData"), &MetaData, Serializer);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("view", View, Serializer);
}

void ULeaderboardDetails::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lbid"), Lbid);
	UBeamJsonUtils::SerializeOptional<UOrderRules*>(TEXT("orules"), &Orules, Serializer);
	Serializer->WriteValue(TEXT("numberOfEntries"), NumberOfEntries);
	Serializer->WriteValue(TEXT("fullName"), FullName);
	UBeamJsonUtils::SerializeOptional<UMetadataView*>(TEXT("metaData"), &MetaData, Serializer);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("view", View, Serializer);		
}

void ULeaderboardDetails ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Lbid = Bag->GetStringField(TEXT("lbid"));
	UBeamJsonUtils::DeserializeOptional<UOrderRules*>("orules", Bag, Orules, OuterOwner);
	NumberOfEntries = Bag->GetIntegerField(TEXT("numberOfEntries"));
	FullName = Bag->GetStringField(TEXT("fullName"));
	UBeamJsonUtils::DeserializeOptional<UMetadataView*>("metaData", Bag, MetaData, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<ULeaderBoardView*>("view", Bag, View, OuterOwner);
}