
#include "BeamableCore/Public/AutoGen/Party.h"
#include "Serialization/BeamJsonUtils.h"



void UParty::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UParty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("leader"), &Leader, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxSize"), &MaxSize, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamGamerTag>, FBeamGamerTag, FString>(TEXT("members"), &Members, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("pendingInvites"), &PendingInvites, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UTagList*>, UTagList*>(TEXT("membersTags"), &MembersTags, Serializer);
}

void UParty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("leader"), &Leader, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxSize"), &MaxSize, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamGamerTag>, FBeamGamerTag, FString>(TEXT("members"), &Members, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("pendingInvites"), &PendingInvites, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UTagList*>, UTagList*>(TEXT("membersTags"), &MembersTags, Serializer);		
}

void UParty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("restriction", Bag, Restriction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamGamerTag, FString>("leader", Bag, Leader, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxSize", Bag, MaxSize, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamGamerTag>, FBeamGamerTag, FString>("members", Bag, Members, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("pendingInvites", Bag, PendingInvites, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, UTagList*>, UTagList*>("membersTags", Bag, MembersTags, OuterOwner);
}



