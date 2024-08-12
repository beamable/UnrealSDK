
#include "BeamableCore/Public/AutoGen/SupportedFederation.h"
#include "Serialization/BeamJsonUtils.h"




void USupportedFederation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UFederationTypeLibrary::FederationTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);
	UBeamJsonUtils::SerializeOptional<UOptionalJsonNodeWrapper*>(TEXT("settings"), &Settings, Serializer);
}

void USupportedFederation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UFederationTypeLibrary::FederationTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);
	UBeamJsonUtils::SerializeOptional<UOptionalJsonNodeWrapper*>(TEXT("settings"), &Settings, Serializer);		
}

void USupportedFederation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Type = UFederationTypeLibrary::SerializationNameToFederationType(Bag->GetStringField(TEXT("type")));
	UBeamJsonUtils::DeserializeOptional<FString>("nameSpace", Bag, NameSpace, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UOptionalJsonNodeWrapper*>("settings", Bag, Settings, OuterOwner);
}



