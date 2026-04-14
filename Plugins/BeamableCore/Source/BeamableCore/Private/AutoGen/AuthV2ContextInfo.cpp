
#include "BeamableCore/Public/AutoGen/AuthV2ContextInfo.h"
#include "Serialization/BeamJsonUtils.h"




void UAuthV2ContextInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
}

void UAuthV2ContextInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);		
}

void UAuthV2ContextInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("platform", Bag, Platform, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("device", Bag, Device, OuterOwner);
}



