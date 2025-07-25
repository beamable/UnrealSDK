
#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UFacebookPaymentUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("object"), Object, Serializer);
	UBeamJsonUtils::SerializeArray<UFacebookUpdatedEntry*>(TEXT("entry"), Entry, Serializer);
}

void UFacebookPaymentUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("object"), Object, Serializer);
	UBeamJsonUtils::SerializeArray<UFacebookUpdatedEntry*>(TEXT("entry"), Entry, Serializer);		
}

void UFacebookPaymentUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("object"), Bag, Object);
	UBeamJsonUtils::DeserializeArray<UFacebookUpdatedEntry*>(TEXT("entry"), Bag, Entry, OuterOwner);
}



