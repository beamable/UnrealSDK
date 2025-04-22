
#include "BeamableCore/Public/AutoGen/Attachment.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UAttachment::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UEntitlementGenerator*>("wrapped", Wrapped, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("state"), State, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("target"), &Target, Serializer);
}

void UAttachment::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UEntitlementGenerator*>("wrapped", Wrapped, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("state"), State, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("target"), &Target, Serializer);		
}

void UAttachment::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeUObject<UEntitlementGenerator*>("wrapped", Bag, Wrapped, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("state")), State);
	UBeamJsonUtils::DeserializeOptional<int64>("target", Bag, Target, OuterOwner);
}



