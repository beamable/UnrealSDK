
#include "BeamableCore/Public/AutoGen/AttachmentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAttachmentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("action"), Action);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("target"), &Target, Serializer);
}

void UAttachmentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("action"), Action);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("target"), &Target, Serializer);		
}

void UAttachmentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	Action = Bag->GetStringField(TEXT("action"));
	UBeamJsonUtils::DeserializeOptional<int32>("quantity", Bag, Quantity, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("specialization", Bag, Specialization, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("target", Bag, Target, OuterOwner);
}



