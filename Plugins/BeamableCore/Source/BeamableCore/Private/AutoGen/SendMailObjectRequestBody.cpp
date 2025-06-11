
#include "BeamableCore/Public/AutoGen/SendMailObjectRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USendMailObjectRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("senderGamerTag"), SenderGamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("category"), Category, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAttachmentRequestBody*>, UAttachmentRequestBody*>(TEXT("attachments"), &Attachments, Serializer);
}

void USendMailObjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("senderGamerTag"), SenderGamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("category"), Category, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAttachmentRequestBody*>, UAttachmentRequestBody*>(TEXT("attachments"), &Attachments, Serializer);		
}

void USendMailObjectRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("senderGamerTag")), SenderGamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("category")), Category);
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("expires", Bag, Expires, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("playerRewards", Bag, PlayerRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("subject", Bag, Subject, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UMailRewards*>("rewards", Bag, Rewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("bodyRef", Bag, BodyRef, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UAttachmentRequestBody*>, UAttachmentRequestBody*>("attachments", Bag, Attachments, OuterOwner);
}



