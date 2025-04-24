
#include "BeamableCore/Public/AutoGen/RouteParameter.h"
#include "Serialization/BeamJsonUtils.h"




void URouteParameter::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("typeName"), TypeName, Serializer);
	UBeamJsonUtils::SerializeOptional<UVariableReference*>(TEXT("variableRef"), &VariableRef, Serializer);
}

void URouteParameter::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("typeName"), TypeName, Serializer);
	UBeamJsonUtils::SerializeOptional<UVariableReference*>(TEXT("variableRef"), &VariableRef, Serializer);		
}

void URouteParameter::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("body")), Body);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("typeName")), TypeName);
	UBeamJsonUtils::DeserializeOptional<UVariableReference*>("variableRef", Bag, VariableRef, OuterOwner);
}



