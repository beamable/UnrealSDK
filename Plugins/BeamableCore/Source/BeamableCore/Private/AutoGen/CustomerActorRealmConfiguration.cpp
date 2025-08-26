
#include "BeamableCore/Public/AutoGen/CustomerActorRealmConfiguration.h"
#include "Serialization/BeamJsonUtils.h"



void UCustomerActorRealmConfiguration::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCustomerActorRealmConfiguration::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);
	UBeamJsonUtils::SerializeUObject<UWebSocketConfiguration*>("websocketConfig", WebsocketConfig, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceUri"), MicroserviceUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceEcrUri"), MicroserviceEcrUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("portalUri"), PortalUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageBrowserUri"), StorageBrowserUri, Serializer);
}

void UCustomerActorRealmConfiguration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);
	UBeamJsonUtils::SerializeUObject<UWebSocketConfiguration*>("websocketConfig", WebsocketConfig, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceUri"), MicroserviceUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceEcrUri"), MicroserviceEcrUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("portalUri"), PortalUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageBrowserUri"), StorageBrowserUri, Serializer);		
}

void UCustomerActorRealmConfiguration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("environment"), Bag, Environment);
	UBeamJsonUtils::DeserializeUObject<UWebSocketConfiguration*>("websocketConfig", Bag, WebsocketConfig, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("microserviceUri"), Bag, MicroserviceUri);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("microserviceEcrUri"), Bag, MicroserviceEcrUri);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("portalUri"), Bag, PortalUri);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("storageBrowserUri"), Bag, StorageBrowserUri);
}



