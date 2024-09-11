
#include "BeamableCore/Public/AutoGen/FederationInfo.h"
#include "Serialization/BeamJsonUtils.h"




void UFederationInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	UBeamJsonUtils::SerializeOptional<UOptionalJsonNodeWrapper*>(TEXT("settings"), &Settings, Serializer);
}

void UFederationInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	UBeamJsonUtils::SerializeOptional<UOptionalJsonNodeWrapper*>(TEXT("settings"), &Settings, Serializer);		
}

void UFederationInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Service = Bag->GetStringField(TEXT("service"));
	Namespace = Bag->GetStringField(TEXT("namespace"));
	UBeamJsonUtils::DeserializeOptional<UOptionalJsonNodeWrapper*>("settings", Bag, Settings, OuterOwner);
}



