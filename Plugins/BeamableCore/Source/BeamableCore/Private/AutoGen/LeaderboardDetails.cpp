
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
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lbid"), Lbid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("numberOfEntries"), NumberOfEntries, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("fullName"), FullName, Serializer);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("view", View, Serializer);
	UBeamJsonUtils::SerializeOptional<UOrderRules*>(TEXT("orules"), &Orules, Serializer);
	UBeamJsonUtils::SerializeOptional<UMetadataView*>(TEXT("metaData"), &MetaData, Serializer);
}

void ULeaderboardDetails::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lbid"), Lbid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("numberOfEntries"), NumberOfEntries, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("fullName"), FullName, Serializer);
	UBeamJsonUtils::SerializeUObject<ULeaderBoardView*>("view", View, Serializer);
	UBeamJsonUtils::SerializeOptional<UOrderRules*>(TEXT("orules"), &Orules, Serializer);
	UBeamJsonUtils::SerializeOptional<UMetadataView*>(TEXT("metaData"), &MetaData, Serializer);		
}

void ULeaderboardDetails::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("lbid")), Lbid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("numberOfEntries")), NumberOfEntries);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("fullName")), FullName);
	UBeamJsonUtils::DeserializeUObject<ULeaderBoardView*>("view", Bag, View, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UOrderRules*>("orules", Bag, Orules, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UMetadataView*>("metaData", Bag, MetaData, OuterOwner);
}



