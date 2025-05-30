
#include "BeamableCore/Public/AutoGen/ServiceRoute.h"





void UServiceRoute::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endpoint"), Endpoint, Serializer);
	Serializer->WriteValue(TEXT("serviceTypeStr"), UBeamJsonUtils::EnumToSerializationName(ServiceTypeStr));
}

void UServiceRoute::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endpoint"), Endpoint, Serializer);
	Serializer->WriteValue(TEXT("serviceTypeStr"), UBeamJsonUtils::EnumToSerializationName(ServiceTypeStr));		
}

void UServiceRoute::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("service")), Service);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("endpoint")), Endpoint);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceTypeStr")), ServiceTypeStr);
}



