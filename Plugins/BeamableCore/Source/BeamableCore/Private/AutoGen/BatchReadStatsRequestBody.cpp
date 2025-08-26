
#include "BeamableCore/Public/AutoGen/BatchReadStatsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBatchReadStatsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("objectIds"), &ObjectIds, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("stats"), &Stats, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("format"), &Format, Serializer);
}

void UBatchReadStatsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("objectIds"), &ObjectIds, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("stats"), &Stats, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("format"), &Format, Serializer);		
}

void UBatchReadStatsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("objectIds"), Bag, ObjectIds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("stats", Bag, Stats, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("format", Bag, Format, OuterOwner);
}



