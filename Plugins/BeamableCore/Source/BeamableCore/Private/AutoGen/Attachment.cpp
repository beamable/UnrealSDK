
#include "BeamableCore/Public/AutoGen/Attachment.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UAttachment::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeUObject<UEntitlementGenerator*>("wrapped", Wrapped, Serializer);
	Serializer->WriteValue(TEXT("state"), State);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("target"), &Target, Serializer);
}

void UAttachment::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeUObject<UEntitlementGenerator*>("wrapped", Wrapped, Serializer);
	Serializer->WriteValue(TEXT("state"), State);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("target"), &Target, Serializer);		
}

void UAttachment::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeUObject<UEntitlementGenerator*>("wrapped", Bag, Wrapped, OuterOwner);
	State = Bag->GetStringField(TEXT("state"));
	UBeamJsonUtils::DeserializeOptional<int64>("target", Bag, Target, OuterOwner);
}



