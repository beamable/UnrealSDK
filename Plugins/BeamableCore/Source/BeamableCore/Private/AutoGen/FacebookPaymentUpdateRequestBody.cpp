
#include "BeamableCore/Public/AutoGen/FacebookPaymentUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UFacebookPaymentUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("object"), Object);
	UBeamJsonUtils::SerializeArray<UFacebookUpdatedEntry*>(TEXT("entry"), Entry, Serializer);
}

void UFacebookPaymentUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("object"), Object);
	UBeamJsonUtils::SerializeArray<UFacebookUpdatedEntry*>(TEXT("entry"), Entry, Serializer);		
}

void UFacebookPaymentUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Object = Bag->GetStringField(TEXT("object"));
	UBeamJsonUtils::DeserializeArray<UFacebookUpdatedEntry*>(Bag->GetArrayField(TEXT("entry")), Entry, OuterOwner);
}



