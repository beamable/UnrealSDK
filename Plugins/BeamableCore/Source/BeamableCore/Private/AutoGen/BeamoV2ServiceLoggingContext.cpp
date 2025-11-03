
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceLoggingContext.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2ServiceLoggingContext::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2ServiceLoggingContext::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("routingKey"), RoutingKey, Serializer);
	Serializer->WriteValue(TEXT("defaultLogLevel"), UBeamJsonUtils::EnumToSerializationName(DefaultLogLevel));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2LogContextRule*>, UBeamoV2LogContextRule*>(TEXT("rules"), &Rules, Serializer);
}

void UBeamoV2ServiceLoggingContext::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("routingKey"), RoutingKey, Serializer);
	Serializer->WriteValue(TEXT("defaultLogLevel"), UBeamJsonUtils::EnumToSerializationName(DefaultLogLevel));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2LogContextRule*>, UBeamoV2LogContextRule*>(TEXT("rules"), &Rules, Serializer);		
}

void UBeamoV2ServiceLoggingContext::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("serviceName"), Bag, ServiceName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("routingKey"), Bag, RoutingKey);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("defaultLogLevel"), Bag, DefaultLogLevel);
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2LogContextRule*>, UBeamoV2LogContextRule*>("rules", Bag, Rules, OuterOwner);
}



