
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
	Domain = Bag->GetStringField(TEXT("domain"));
	ObjectType = Bag->GetStringField(TEXT("objectType"));
	Access = Bag->GetStringField(TEXT("access"));
	UBeamJsonUtils::DeserializeArray<UStatsSearchCriteria*>(Bag->GetArrayField(TEXT("criteria")), Criteria, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("statKeys")), StatKeys, OuterOwner);
}



