
#include "AutoGen/BatchReadStatsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBatchReadStatsRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("objectIds"), ObjectIds);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("stats"), &Stats, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("format"), &Format, Serializer);
}

void UBatchReadStatsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("objectIds"), ObjectIds);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("stats"), &Stats, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("format"), &Format, Serializer);		
}

void UBatchReadStatsRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ObjectIds = Bag->GetStringField(TEXT("objectIds"));
	UBeamJsonUtils::DeserializeOptional<FString>("stats", Bag, Stats, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("format", Bag, Format, OuterOwner);
}