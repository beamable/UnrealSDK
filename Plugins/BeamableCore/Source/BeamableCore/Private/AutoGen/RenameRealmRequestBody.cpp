
#include "BeamableCore/Public/AutoGen/RenameRealmRequestBody.h"





void URenameRealmRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("newName"), NewName, Serializer);
}

void URenameRealmRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("newName"), NewName, Serializer);		
}

void URenameRealmRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("newName"), Bag, NewName);
}



