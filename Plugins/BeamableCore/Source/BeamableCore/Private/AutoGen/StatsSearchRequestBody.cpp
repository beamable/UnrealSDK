
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("domain")), Domain);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("access")), Access);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("objectType")), ObjectType);
	UBeamJsonUtils::DeserializeArray<UStatsSearchCriteria*>(Bag->GetArrayField(TEXT("criteria")), Criteria, OuterOwner);
}



