
#include "BeamableCore/Public/AutoGen/Message.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("receiverGamerTag"), ReceiverGamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("state"), State, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("senderGamerTag"), SenderGamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sent"), Sent, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("category"), Category, Serializer);
	UBeamJsonUtils::SerializeArray<UAttachment*>(TEXT("attachments"), Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("claimedTimeMs"), &ClaimedTimeMs, Serializer);
}

void UMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("receiverGamerTag"), ReceiverGamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("state"), State, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("senderGamerTag"), SenderGamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sent"), Sent, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("category"), Category, Serializer);
	UBeamJsonUtils::SerializeArray<UAttachment*>(TEXT("attachments"), Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("claimedTimeMs"), &ClaimedTimeMs, Serializer);		
}

void UMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("receiverGamerTag")), ReceiverGamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("state")), State);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("senderGamerTag")), SenderGamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sent")), Sent);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("category")), Category);
	UBeamJsonUtils::DeserializeArray<UAttachment*>(Bag->GetArrayField(TEXT("attachments")), Attachments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expires", Bag, Expires, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("playerRewards", Bag, PlayerRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("subject", Bag, Subject, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UMailRewards*>("rewards", Bag, Rewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("bodyRef", Bag, BodyRef, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("claimedTimeMs", Bag, ClaimedTimeMs, OuterOwner);
}



