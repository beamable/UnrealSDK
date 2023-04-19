
#include "BeamableCore/Public/AutoGen/AnnouncementAttachment.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UAnnouncementAttachment::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("count"), Count);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAttachmentProperty*>, UAttachmentProperty*>(TEXT("properties"), &Properties, Serializer);
}

void UAnnouncementAttachment::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("count"), Count);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAttachmentProperty*>, UAttachmentProperty*>(TEXT("properties"), &Properties, Serializer);		
}

void UAnnouncementAttachment::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	Count = Bag->GetIntegerField(TEXT("count"));
	UBeamJsonUtils::DeserializeOptional<FString>("type", Bag, Type, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UAttachmentProperty*>, UAttachmentProperty*>("properties", Bag, Properties, OuterOwner);
}



