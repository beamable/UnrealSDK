
#include "AutoGen/MailBasicMessage.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UMailBasicMessage ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	Serializer->WriteValue(TEXT("receiverGamerTag"), ReceiverGamerTag);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	Serializer->WriteValue(TEXT("state"), State);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("senderGamerTag"), SenderGamerTag);
	Serializer->WriteValue(TEXT("sent"), Sent);
	Serializer->WriteValue(TEXT("category"), Category);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeArray<UAttachment*>(TEXT("attachments"), Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("claimedTimeMs"), &ClaimedTimeMs, Serializer);
}

void UMailBasicMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("playerRewards"), &PlayerRewards, Serializer);
	Serializer->WriteValue(TEXT("receiverGamerTag"), ReceiverGamerTag);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	Serializer->WriteValue(TEXT("state"), State);
	UBeamJsonUtils::SerializeOptional<UMailRewards*>(TEXT("rewards"), &Rewards, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("senderGamerTag"), SenderGamerTag);
	Serializer->WriteValue(TEXT("sent"), Sent);
	Serializer->WriteValue(TEXT("category"), Category);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("bodyRef"), &BodyRef, Serializer);
	UBeamJsonUtils::SerializeArray<UAttachment*>(TEXT("attachments"), Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("claimedTimeMs"), &ClaimedTimeMs, Serializer);		
}

void UMailBasicMessage ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("expires", Bag, Expires, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("playerRewards", Bag, PlayerRewards, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("receiverGamerTag")), ReceiverGamerTag);
	UBeamJsonUtils::DeserializeOptional<FString>("subject", Bag, Subject, OuterOwner);
	State = Bag->GetStringField(TEXT("state"));
	UBeamJsonUtils::DeserializeOptional<UMailRewards*>("rewards", Bag, Rewards, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("senderGamerTag")), SenderGamerTag);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("sent")), Sent);
	Category = Bag->GetStringField(TEXT("category"));
	UBeamJsonUtils::DeserializeOptional<int64>("bodyRef", Bag, BodyRef, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UAttachment*>(Bag->GetArrayField(TEXT("attachments")), Attachments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("claimedTimeMs", Bag, ClaimedTimeMs, OuterOwner);
}