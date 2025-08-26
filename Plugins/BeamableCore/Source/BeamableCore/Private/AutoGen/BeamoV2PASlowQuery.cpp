
#include "BeamableCore/Public/AutoGen/BeamoV2PASlowQuery.h"





void UBeamoV2PASlowQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("line"), Line, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
}

void UBeamoV2PASlowQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("line"), Line, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);		
}

void UBeamoV2PASlowQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("line"), Bag, Line);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("namespace"), Bag, Namespace);
}



