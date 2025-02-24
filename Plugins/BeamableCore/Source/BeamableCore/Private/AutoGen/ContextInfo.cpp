
#include "BeamableCore/Public/AutoGen/ContextInfo.h"
#include "Serialization/BeamJsonUtils.h"




void UContextInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
}

void UContextInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);		
}

void UContextInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("platform", Bag, Platform, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("device", Bag, Device, OuterOwner);
}



