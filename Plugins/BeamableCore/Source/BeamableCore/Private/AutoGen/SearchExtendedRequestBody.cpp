
#include "BeamableCore/Public/AutoGen/SearchExtendedRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USearchExtendedRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("domain"), Domain);
	Serializer->WriteValue(TEXT("objectType"), ObjectType);
	Serializer->WriteValue(TEXT("access"), Access);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("statKeys"), StatKeys, Serializer);
}

void USearchExtendedRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("domain"), Domain);
	Serializer->WriteValue(TEXT("objectType"), ObjectType);
	Serializer->WriteValue(TEXT("access"), Access);
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("statKeys"), StatKeys, Serializer);		
}

void USearchExtendedRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("domain")), Domain);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("objectType")), ObjectType);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("access")), Access);
	UBeamJsonUtils::DeserializeArray<UStatsSearchCriteria*>(Bag->GetArrayField(TEXT("criteria")), Criteria, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("statKeys")), StatKeys, OuterOwner);
}



