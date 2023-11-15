
#include "BeamableCore/Public/AutoGen/Message.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("receiverGamerTag"), ReceiverGamerTag);
	Serializer->WriteValue(TEXT("state"), State);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("senderGamerTag"), SenderGamerTag);
	Serializer->WriteValue(TEXT("sent"), Sent);
	Serializer->WriteValue(TEXT("category"), Category);
	UBeamJsonUtils::SerializeArray<UAttachment*>(TEXT("attachments"), Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("claimedTimeMs"), &ClaimedTimeMs, Serializer);
}

void UMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("receiverGamerTag"), ReceiverGamerTag);
	Serializer->WriteValue(TEXT("state"), State);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("senderGamerTag"), SenderGamerTag);
	Serializer->WriteValue(TEXT("sent"), Sent);
	Serializer->WriteValue(TEXT("category"), Category);
	UBeamJsonUtils::SerializeArray<UAttachment*>(TEXT("attachments"), Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("claimedTimeMs"), &ClaimedTimeMs, Serializer);		
}

void UMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("receiverGamerTag")), ReceiverGamerTag);
	State = Bag->GetStringField(TEXT("state"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("senderGamerTag")), SenderGamerTag);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("sent")), Sent);
	Category = Bag->GetStringField(TEXT("category"));
	UBeamJsonUtils::DeserializeArray<UAttachment*>(Bag->GetArrayField(TEXT("attachments")), Attachments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("expires", Bag, Expires, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("playerRewards", Bag, PlayerRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("subject", Bag, Subject, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UMailRewards*>("rewards", Bag, Rewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("bodyRef", Bag, BodyRef, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("claimedTimeMs", Bag, ClaimedTimeMs, OuterOwner);
}



