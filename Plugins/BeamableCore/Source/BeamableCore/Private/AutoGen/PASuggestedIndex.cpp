
#include "BeamableCore/Public/AutoGen/PASuggestedIndex.h"
#include "Serialization/BeamJsonUtils.h"




void UPASuggestedIndex::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("weight"), Weight, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("impact"), Impact, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("index"), Index, Serializer);
}

void UPASuggestedIndex::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("weight"), Weight, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("impact"), Impact, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("index"), Index, Serializer);		
}

void UPASuggestedIndex::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("weight"), Bag, Weight);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("namespace"), Bag, Namespace);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("impact"), Bag, Impact, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("index"), Bag, Index, OuterOwner);
}



