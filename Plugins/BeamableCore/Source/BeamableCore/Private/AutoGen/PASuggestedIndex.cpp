
#include "BeamableCore/Public/AutoGen/PASuggestedIndex.h"
#include "Serialization/BeamJsonUtils.h"




void UPASuggestedIndex::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("weight"), Weight);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("impact"), Impact, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("index"), Index, Serializer);
}

void UPASuggestedIndex::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("weight"), Weight);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("impact"), Impact, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("index"), Index, Serializer);		
}

void UPASuggestedIndex::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("weight")), Weight);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("namespace")), Namespace);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("impact")), Impact, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("index")), Index, OuterOwner);
}



