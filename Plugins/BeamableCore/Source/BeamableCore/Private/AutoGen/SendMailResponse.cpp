
#include "AutoGen/SendMailResponse.h"
#include "Serialization/BeamJsonUtils.h"


void USendMailResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("mailId"), &MailId, Serializer);
}

void USendMailResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("mailId"), &MailId, Serializer);		
}

void USendMailResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("mailId", Bag, MailId, OuterOwner);
}