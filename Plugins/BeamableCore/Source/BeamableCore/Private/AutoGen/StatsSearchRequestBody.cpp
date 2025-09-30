
#include "BeamableCore/Public/AutoGen/StatsSearchRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatsSearchRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("domain"), Domain, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectType"), ObjectType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("access"), Access, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
}

void UStatsSearchRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("domain"), Domain, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectType"), ObjectType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("access"), Access, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);		
}

void UStatsSearchRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("domain"), Bag, Domain);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("objectType"), Bag, ObjectType);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("access"), Bag, Access);
	UBeamJsonUtils::DeserializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Bag, Criteria, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("offset", Bag, Offset, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
}



