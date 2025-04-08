
#include "BeamableCore/Public/AutoGen/ReplaceObjectsRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UReplaceObjectsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourcePlayerId"), SourcePlayerId);
	Serializer->WriteValue(TEXT("targetPlayerId"), TargetPlayerId);
}

void UReplaceObjectsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourcePlayerId"), SourcePlayerId);
	Serializer->WriteValue(TEXT("targetPlayerId"), TargetPlayerId);		
}

void UReplaceObjectsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sourcePlayerId")), SourcePlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("targetPlayerId")), TargetPlayerId);
}



