
#include "BeamableCore/Public/AutoGen/RealmsBasicRealmConfiguration.h"
#include "Serialization/BeamJsonUtils.h"



void URealmsBasicRealmConfiguration::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmsBasicRealmConfiguration::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UWebSocketConfiguration*>("websocketConfig", WebsocketConfig, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceURI"), MicroserviceURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("portalURI"), PortalURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceEcrURI"), MicroserviceEcrURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageBrowserURI"), StorageBrowserURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);
}

void URealmsBasicRealmConfiguration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UWebSocketConfiguration*>("websocketConfig", WebsocketConfig, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceURI"), MicroserviceURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("portalURI"), PortalURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceEcrURI"), MicroserviceEcrURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageBrowserURI"), StorageBrowserURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);		
}

void URealmsBasicRealmConfiguration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UWebSocketConfiguration*>("websocketConfig", Bag, WebsocketConfig, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("microserviceURI"), Bag, MicroserviceURI);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("portalURI"), Bag, PortalURI);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("microserviceEcrURI"), Bag, MicroserviceEcrURI);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("storageBrowserURI"), Bag, StorageBrowserURI);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("environment"), Bag, Environment);
}



