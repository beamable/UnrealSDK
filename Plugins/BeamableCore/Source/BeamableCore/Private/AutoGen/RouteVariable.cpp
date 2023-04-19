
#include "BeamableCore/Public/AutoGen/RouteVariable.h"





void URouteVariable::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("typeName"), TypeName);
}

void URouteVariable::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("typeName"), TypeName);		
}

void URouteVariable::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	TypeName = Bag->GetStringField(TEXT("typeName"));
}



