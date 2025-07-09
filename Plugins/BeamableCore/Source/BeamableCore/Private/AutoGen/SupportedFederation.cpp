
#include "BeamableCore/Public/AutoGen/SupportedFederation.h"
#include "Serialization/BeamJsonUtils.h"




void USupportedFederation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamFederationType>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);
}

void USupportedFederation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamFederationType>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nameSpace"), &NameSpace, Serializer);		
}

void USupportedFederation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<EBeamFederationType>("type", Bag, Type, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("nameSpace", Bag, NameSpace, OuterOwner);
}



