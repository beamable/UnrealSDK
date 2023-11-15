
#include "BeamableCore/Public/AutoGen/ProjectView.h"
#include "Serialization/BeamJsonUtils.h"



void UProjectView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UProjectView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamPid>, FBeamPid, FString>(TEXT("children"), &Children, Serializer);
}

void UProjectView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamPid>, FBeamPid, FString>(TEXT("children"), &Children, Serializer);		
}

void UProjectView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProjectName = Bag->GetStringField(TEXT("projectName"));
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("pid")), Pid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("sharded", Bag, bSharded, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("secret", Bag, Secret, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("parent", Bag, Parent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, int64>("cid", Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamPid>, FBeamPid, FString>("children", Bag, Children, OuterOwner);
}



