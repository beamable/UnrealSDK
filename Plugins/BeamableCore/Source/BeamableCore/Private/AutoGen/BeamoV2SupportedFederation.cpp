
#include "BeamableCore/Public/AutoGen/BeamoV2SupportedFederation.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2SupportedFederation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamBeamoV2FederationType>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);
}

void UBeamoV2SupportedFederation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamBeamoV2FederationType>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);		
}

void UBeamoV2SupportedFederation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<EBeamBeamoV2FederationType>("type", Bag, Type, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("nameSpace", Bag, NameSpace, OuterOwner);
}



