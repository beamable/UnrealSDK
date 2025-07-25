
#include "BeamableCore/Public/AutoGen/FederationInfo.h"
#include "Serialization/BeamJsonUtils.h"




void UFederationInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
	UBeamJsonUtils::SerializeJsonObject(TEXT("settings"), Settings, Serializer);
}

void UFederationInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
	UBeamJsonUtils::SerializeJsonObject(TEXT("settings"), Settings, Serializer);		
}

void UFederationInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("service"), Bag, Service);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("namespace"), Bag, Namespace);
	UBeamJsonUtils::DeserializeJsonObject(TEXT("settings"), Bag, Settings, OuterOwner);
}



