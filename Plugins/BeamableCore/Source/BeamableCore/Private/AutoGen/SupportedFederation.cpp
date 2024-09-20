
#include "BeamableCore/Public/AutoGen/SupportedFederation.h"
#include "Serialization/BeamJsonUtils.h"




void USupportedFederation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UFederationTypeLibrary::FederationTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeJsonObject(TEXT("settings"), Settings, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);
}

void USupportedFederation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UFederationTypeLibrary::FederationTypeToSerializationName(Type));
	UBeamJsonUtils::SerializeJsonObject(TEXT("settings"), Settings, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);		
}

void USupportedFederation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Type = UFederationTypeLibrary::SerializationNameToFederationType(Bag->GetStringField(TEXT("type")));
	UBeamJsonUtils::DeserializeJsonObject(TEXT("settings"), Bag, Settings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("nameSpace", Bag, NameSpace, OuterOwner);
}



