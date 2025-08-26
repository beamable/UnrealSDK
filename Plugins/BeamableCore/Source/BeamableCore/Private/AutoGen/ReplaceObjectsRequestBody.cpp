
#include "BeamableCore/Public/AutoGen/ReplaceObjectsRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UReplaceObjectsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourcePlayerId"), SourcePlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("targetPlayerId"), TargetPlayerId, Serializer);
}

void UReplaceObjectsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourcePlayerId"), SourcePlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("targetPlayerId"), TargetPlayerId, Serializer);		
}

void UReplaceObjectsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("sourcePlayerId"), Bag, SourcePlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("targetPlayerId"), Bag, TargetPlayerId);
}



