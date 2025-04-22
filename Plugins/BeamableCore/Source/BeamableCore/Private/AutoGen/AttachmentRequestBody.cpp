
#include "BeamableCore/Public/AutoGen/AttachmentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAttachmentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("action"), Action, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("target"), &Target, Serializer);
}

void UAttachmentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("action"), Action, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("target"), &Target, Serializer);		
}

void UAttachmentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("action")), Action);
	UBeamJsonUtils::DeserializeOptional<int32>("quantity", Bag, Quantity, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("specialization", Bag, Specialization, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("target", Bag, Target, OuterOwner);
}



