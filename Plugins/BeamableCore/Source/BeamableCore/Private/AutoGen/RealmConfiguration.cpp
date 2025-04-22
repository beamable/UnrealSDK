
#include "BeamableCore/Public/AutoGen/RealmConfiguration.h"
#include "Serialization/BeamJsonUtils.h"



void URealmConfiguration::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmConfiguration::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UWebSocketConfiguration*>("websocketConfig", WebsocketConfig, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceURI"), MicroserviceURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("portalURI"), PortalURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceEcrURI"), MicroserviceEcrURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageBrowserURI"), StorageBrowserURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);
}

void URealmConfiguration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UWebSocketConfiguration*>("websocketConfig", WebsocketConfig, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceURI"), MicroserviceURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("portalURI"), PortalURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("microserviceEcrURI"), MicroserviceEcrURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("storageBrowserURI"), StorageBrowserURI, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("environment"), Environment, Serializer);		
}

void URealmConfiguration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UWebSocketConfiguration*>("websocketConfig", Bag, WebsocketConfig, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("microserviceURI")), MicroserviceURI);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("portalURI")), PortalURI);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("microserviceEcrURI")), MicroserviceEcrURI);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("storageBrowserURI")), StorageBrowserURI);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("environment")), Environment);
}



