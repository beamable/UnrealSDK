
#include "BeamableCore/Public/AutoGen/AnnouncementAttachment.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UAnnouncementAttachment::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("count"), Count, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAttachmentProperty*>, UAttachmentProperty*>(TEXT("properties"), &Properties, Serializer);
}

void UAnnouncementAttachment::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("count"), Count, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAttachmentProperty*>, UAttachmentProperty*>(TEXT("properties"), &Properties, Serializer);		
}

void UAnnouncementAttachment::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("count")), Count);
	UBeamJsonUtils::DeserializeOptional<FString>("type", Bag, Type, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UAttachmentProperty*>, UAttachmentProperty*>("properties", Bag, Properties, OuterOwner);
}



