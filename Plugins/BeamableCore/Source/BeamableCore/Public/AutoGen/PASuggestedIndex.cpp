
#include "AutoGen/PASuggestedIndex.h"
#include "Serialization/BeamJsonUtils.h"


void UPASuggestedIndex ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("weight"), Weight);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("impact"), Impact, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("index"), Index, Serializer);
}

void UPASuggestedIndex::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("weight"), Weight);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("impact"), Impact, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("index"), Index, Serializer);		
}

void UPASuggestedIndex ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Weight = Bag->GetStringField(TEXT("weight"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("impact")), Impact, OuterOwner);
	Id = Bag->GetStringField(TEXT("id"));
	Namespace = Bag->GetStringField(TEXT("namespace"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("index")), Index, OuterOwner);
}