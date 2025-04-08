
#include "BeamableCore/Public/AutoGen/StatsSearchRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatsSearchRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("domain"), Domain);
	Serializer->WriteValue(TEXT("access"), Access);
	Serializer->WriteValue(TEXT("objectType"), ObjectType);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
}

void UStatsSearchRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("domain"), Domain);
	Serializer->WriteValue(TEXT("access"), Access);
	Serializer->WriteValue(TEXT("objectType"), ObjectType);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);		
}

void UStatsSearchRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("domain")), Domain);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("access")), Access);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("objectType")), ObjectType);
	UBeamJsonUtils::DeserializeArray<UStatsSearchCriteria*>(Bag->GetArrayField(TEXT("criteria")), Criteria, OuterOwner);
}



