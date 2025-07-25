
#include "BeamableCore/Public/AutoGen/BeamoV2PASuggestedIndex.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UBeamoV2PASuggestedIndex::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("weight"), Weight, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("impact"), Impact, Serializer);
	UBeamJsonUtils::SerializeArray<FMapOfInt32>(TEXT("index"), Index, Serializer);
}

void UBeamoV2PASuggestedIndex::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("weight"), Weight, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("impact"), Impact, Serializer);
	UBeamJsonUtils::SerializeArray<FMapOfInt32>(TEXT("index"), Index, Serializer);		
}

void UBeamoV2PASuggestedIndex::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("namespace"), Bag, Namespace);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("weight"), Bag, Weight);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("impact"), Bag, Impact, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FMapOfInt32>(TEXT("index"), Bag, Index, OuterOwner);
}



