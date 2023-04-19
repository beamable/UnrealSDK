
#include "BeamableCore/Public/AutoGen/RoleMapping.h"





void URoleMapping::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectId"), ProjectId);
	Serializer->WriteValue(TEXT("role"), Role);
}

void URoleMapping::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectId"), ProjectId);
	Serializer->WriteValue(TEXT("role"), Role);		
}

void URoleMapping::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProjectId = Bag->GetStringField(TEXT("projectId"));
	Role = Bag->GetStringField(TEXT("role"));
}



