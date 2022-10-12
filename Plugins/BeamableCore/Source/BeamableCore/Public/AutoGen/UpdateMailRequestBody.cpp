
#include "AutoGen/UpdateMailRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UUpdateMailRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("state"), &State, Serializer);
	Serializer->WriteValue(TEXT("mailId"), MailId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("acceptAttachments"), &bAcceptAttachments, Serializer);
}

void UUpdateMailRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("state"), &State, Serializer);
	Serializer->WriteValue(TEXT("mailId"), MailId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("acceptAttachments"), &bAcceptAttachments, Serializer);		
}

void UUpdateMailRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("expires", Bag, Expires, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("subject", Bag, Subject, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("state", Bag, State, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("mailId")), MailId);
	UBeamJsonUtils::DeserializeOptional<FString>("category", Bag, Category, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("acceptAttachments", Bag, bAcceptAttachments, OuterOwner);
}