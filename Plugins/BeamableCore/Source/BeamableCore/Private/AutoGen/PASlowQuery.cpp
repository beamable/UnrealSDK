
#include "BeamableCore/Public/AutoGen/PASlowQuery.h"





void UPASlowQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("line"), Line, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
}

void UPASlowQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("line"), Line, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);		
}

void UPASlowQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("line"), Bag, Line);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("namespace"), Bag, Namespace);
}



