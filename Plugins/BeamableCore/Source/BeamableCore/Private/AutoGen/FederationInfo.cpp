
#include "BeamableCore/Public/AutoGen/FederationInfo.h"
#include "Serialization/BeamJsonUtils.h"




void UFederationInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	UBeamJsonUtils::SerializeJsonObject(TEXT("settings"), Settings, Serializer);
}

void UFederationInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	UBeamJsonUtils::SerializeJsonObject(TEXT("settings"), Settings, Serializer);		
}

void UFederationInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("service")), Service);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("namespace")), Namespace);
	UBeamJsonUtils::DeserializeJsonObject(TEXT("settings"), Bag, Settings, OuterOwner);
}



