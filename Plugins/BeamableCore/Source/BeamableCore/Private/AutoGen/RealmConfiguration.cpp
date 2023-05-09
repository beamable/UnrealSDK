
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
	Serializer->WriteValue(TEXT("microserviceURI"), MicroserviceURI);
	Serializer->WriteValue(TEXT("portalURI"), PortalURI);
	Serializer->WriteValue(TEXT("microserviceEcrURI"), MicroserviceEcrURI);
	Serializer->WriteValue(TEXT("storageBrowserURI"), StorageBrowserURI);
	Serializer->WriteValue(TEXT("environment"), Environment);
}

void URealmConfiguration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UWebSocketConfiguration*>("websocketConfig", WebsocketConfig, Serializer);
	Serializer->WriteValue(TEXT("microserviceURI"), MicroserviceURI);
	Serializer->WriteValue(TEXT("portalURI"), PortalURI);
	Serializer->WriteValue(TEXT("microserviceEcrURI"), MicroserviceEcrURI);
	Serializer->WriteValue(TEXT("storageBrowserURI"), StorageBrowserURI);
	Serializer->WriteValue(TEXT("environment"), Environment);		
}

void URealmConfiguration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UWebSocketConfiguration*>("websocketConfig", Bag, WebsocketConfig, OuterOwner);
	MicroserviceURI = Bag->GetStringField(TEXT("microserviceURI"));
	PortalURI = Bag->GetStringField(TEXT("portalURI"));
	MicroserviceEcrURI = Bag->GetStringField(TEXT("microserviceEcrURI"));
	StorageBrowserURI = Bag->GetStringField(TEXT("storageBrowserURI"));
	Environment = Bag->GetStringField(TEXT("environment"));
}



