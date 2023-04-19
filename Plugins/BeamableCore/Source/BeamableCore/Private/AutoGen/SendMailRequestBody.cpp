
#include "BeamableCore/Public/AutoGen/SendMailRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USendMailRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("receiverGamerTag"), ReceiverGamerTag);
	Serializer->WriteValue(TEXT("senderGamerTag"), SenderGamerTag);
	Serializer->WriteValue(TEXT("category"), Category);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAttachmentRequestBody*>, UAttachmentRequestBody*>(TEXT("attachments"), &Attachments, Serializer);
}

void USendMailRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("receiverGamerTag"), ReceiverGamerTag);
	Serializer->WriteValue(TEXT("senderGamerTag"), SenderGamerTag);
	Serializer->WriteValue(TEXT("category"), Category);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAttachmentRequestBody*>, UAttachmentRequestBody*>(TEXT("attachments"), &Attachments, Serializer);		
}

void USendMailRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("receiverGamerTag")), ReceiverGamerTag);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("senderGamerTag")), SenderGamerTag);
	Category = Bag->GetStringField(TEXT("category"));
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("expires", Bag, Expires, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("playerRewards", Bag, PlayerRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("subject", Bag, Subject, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UMailRewards*>("rewards", Bag, Rewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("bodyRef", Bag, BodyRef, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UAttachmentRequestBody*>, UAttachmentRequestBody*>("attachments", Bag, Attachments, OuterOwner);
}



