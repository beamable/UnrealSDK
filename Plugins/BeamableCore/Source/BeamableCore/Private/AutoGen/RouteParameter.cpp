
#include "BeamableCore/Public/AutoGen/RouteParameter.h"
#include "Serialization/BeamJsonUtils.h"




void URouteParameter::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("typeName"), TypeName);
	UBeamJsonUtils::SerializeOptional<UVariableReference*>(TEXT("variableRef"), &VariableRef, Serializer);
}

void URouteParameter::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("typeName"), TypeName);
	UBeamJsonUtils::SerializeOptional<UVariableReference*>(TEXT("variableRef"), &VariableRef, Serializer);		
}

void URouteParameter::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	Body = Bag->GetStringField(TEXT("body"));
	TypeName = Bag->GetStringField(TEXT("typeName"));
	UBeamJsonUtils::DeserializeOptional<UVariableReference*>("variableRef", Bag, VariableRef, OuterOwner);
}



