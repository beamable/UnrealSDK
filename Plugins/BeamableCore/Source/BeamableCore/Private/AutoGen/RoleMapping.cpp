
#include "BeamableCore/Public/AutoGen/RoleMapping.h"





void URoleMapping::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectId"), ProjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("role"), Role, Serializer);
}

void URoleMapping::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectId"), ProjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("role"), Role, Serializer);		
}

void URoleMapping::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("projectId"), Bag, ProjectId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("role"), Bag, Role);
}



