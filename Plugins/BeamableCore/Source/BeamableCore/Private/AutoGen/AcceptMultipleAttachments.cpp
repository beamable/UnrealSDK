
#include "BeamableCore/Public/AutoGen/AcceptMultipleAttachments.h"
#include "Serialization/BeamJsonUtils.h"




void UAcceptMultipleAttachments::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int64>(TEXT("mailIds"), MailIds, Serializer);
}

void UAcceptMultipleAttachments::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int64>(TEXT("mailIds"), MailIds, Serializer);		
}

void UAcceptMultipleAttachments::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("mailIds")), MailIds, OuterOwner);
}



