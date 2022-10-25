
#include "AutoGen/ProjectView.h"
#include "Serialization/BeamJsonUtils.h"


void UProjectView ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	Serializer->WriteValue(TEXT("pid"), Pid);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);
}

void UProjectView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	Serializer->WriteValue(TEXT("pid"), Pid);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);		
}

void UProjectView ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProjectName = Bag->GetStringField(TEXT("projectName"));
	Pid = Bag->GetStringField(TEXT("pid"));
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("sharded", Bag, bSharded, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("secret", Bag, Secret, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("parent", Bag, Parent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("cid", Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("children", Bag, Children, OuterOwner);
}