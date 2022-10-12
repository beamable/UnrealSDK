
#include "AutoGen/MailResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UMailResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UMailObjectMessage*>(TEXT("result"), &Result, Serializer);
}

void UMailResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UMailObjectMessage*>(TEXT("result"), &Result, Serializer);		
}

void UMailResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<UMailObjectMessage*>("result", Bag, Result, OuterOwner);
}