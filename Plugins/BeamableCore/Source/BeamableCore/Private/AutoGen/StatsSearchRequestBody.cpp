
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
	Domain = Bag->GetStringField(TEXT("domain"));
	Access = Bag->GetStringField(TEXT("access"));
	ObjectType = Bag->GetStringField(TEXT("objectType"));
	UBeamJsonUtils::DeserializeArray<UStatsSearchCriteria*>(Bag->GetArrayField(TEXT("criteria")), Criteria, OuterOwner);
}



