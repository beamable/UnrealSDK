
#include "BeamableCore/Public/AutoGen/SupportedFederation.h"
#include "Serialization/BeamJsonUtils.h"




void USupportedFederation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeJsonObject(TEXT("settings"), Settings, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);
}

void USupportedFederation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeJsonObject(TEXT("settings"), Settings, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);		
}

void USupportedFederation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);
	UBeamJsonUtils::DeserializeJsonObject(TEXT("settings"), Bag, Settings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("nameSpace", Bag, NameSpace, OuterOwner);
}



