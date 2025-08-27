
#include "BeamableCore/Public/AutoGen/StatsSearchRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatsSearchRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("domain"), Domain, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("access"), Access, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectType"), ObjectType, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
}

void UStatsSearchRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("domain"), Domain, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("access"), Access, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectType"), ObjectType, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);		
}

void UStatsSearchRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("domain"), Bag, Domain);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("access"), Bag, Access);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("objectType"), Bag, ObjectType);
	UBeamJsonUtils::DeserializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Bag, Criteria, OuterOwner);
}



