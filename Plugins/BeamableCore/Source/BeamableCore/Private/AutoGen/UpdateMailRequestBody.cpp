
#include "BeamableCore/Public/AutoGen/UpdateMailRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UUpdateMailRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mailId"), MailId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("acceptAttachments"), &bAcceptAttachments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("state"), &State, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);
}

void UUpdateMailRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mailId"), MailId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("acceptAttachments"), &bAcceptAttachments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subject"), &Subject, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("state"), &State, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);		
}

void UUpdateMailRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("mailId")), MailId);
	UBeamJsonUtils::DeserializeOptional<bool>("acceptAttachments", Bag, bAcceptAttachments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("expires", Bag, Expires, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("subject", Bag, Subject, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("state", Bag, State, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("category", Bag, Category, OuterOwner);
}



