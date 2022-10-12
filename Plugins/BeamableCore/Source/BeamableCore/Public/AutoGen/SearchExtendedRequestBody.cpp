
#include "AutoGen/SearchExtendedRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void USearchExtendedRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
	Serializer->WriteValue(TEXT("domain"), Domain);
	Serializer->WriteValue(TEXT("objectType"), ObjectType);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("statKeys"), StatKeys, Serializer);
	Serializer->WriteValue(TEXT("access"), Access);
}

void USearchExtendedRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UStatsSearchCriteria*>(TEXT("criteria"), Criteria, Serializer);
	Serializer->WriteValue(TEXT("domain"), Domain);
	Serializer->WriteValue(TEXT("objectType"), ObjectType);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("statKeys"), StatKeys, Serializer);
	Serializer->WriteValue(TEXT("access"), Access);		
}

void USearchExtendedRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UStatsSearchCriteria*>(Bag->GetArrayField(TEXT("criteria")), Criteria, OuterOwner);
	Domain = Bag->GetStringField(TEXT("domain"));
	ObjectType = Bag->GetStringField(TEXT("objectType"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("statKeys")), StatKeys, OuterOwner);
	Access = Bag->GetStringField(TEXT("access"));
}