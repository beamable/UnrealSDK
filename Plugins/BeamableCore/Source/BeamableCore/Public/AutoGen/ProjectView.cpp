
#include "AutoGen/ProjectView.h"
#include "Serialization/BeamJsonUtils.h"


void UProjectView ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("cid"), &Cid, Serializer);
	Serializer->WriteValue(TEXT("pid"), Pid);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
}

void UProjectView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("cid"), &Cid, Serializer);
	Serializer->WriteValue(TEXT("pid"), Pid);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);		
}

void UProjectView ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("secret", Bag, Secret, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("parent", Bag, Parent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("children", Bag, Children, OuterOwner);
	ProjectName = Bag->GetStringField(TEXT("projectName"));
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("cid", Bag, Cid, OuterOwner);
	Pid = Bag->GetStringField(TEXT("pid"));
	UBeamJsonUtils::DeserializeOptional<bool>("sharded", Bag, bSharded, OuterOwner);
}