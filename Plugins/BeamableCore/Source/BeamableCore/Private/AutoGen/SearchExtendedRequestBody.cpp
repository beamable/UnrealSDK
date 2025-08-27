
#include "BeamableCore/Public/AutoGen/SearchExtendedRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USearchExtendedRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("domain"), Domain, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectType"), ObjectType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("access"), Access, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("statKeys"), StatKeys, Serializer);
}

void USearchExtendedRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("domain"), Domain, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectType"), ObjectType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("access"), Access, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("statKeys"), StatKeys, Serializer);		
}

void USearchExtendedRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("domain"), Bag, Domain);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("objectType"), Bag, ObjectType);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("access"), Bag, Access);
	UBeamJsonUtils::DeserializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Bag, Criteria, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("statKeys"), Bag, StatKeys, OuterOwner);
}



