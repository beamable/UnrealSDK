
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("object")), Object);
	UBeamJsonUtils::DeserializeArray<UFacebookUpdatedEntry*>(Bag->GetArrayField(TEXT("entry")), Entry, OuterOwner);
}



