
#include "BeamableCore/Public/AutoGen/PASlowQuery.h"





void UPASlowQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("line"), Line);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
}

void UPASlowQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("line"), Line);
	Serializer->WriteValue(TEXT("namespace"), Namespace);		
}

void UPASlowQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("line")), Line);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("namespace")), Namespace);
}



